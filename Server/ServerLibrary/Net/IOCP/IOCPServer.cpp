#include "stdafx.h"

IOCPServer::IOCPServer(ContentsProcess *process) : Server("IOCPServer", process),
	listenSocket(INVALID_SOCKET), iocp(nullptr) {
	bool result = this->initialize(json.getDocument());
	if(!result) {
		SystemLogger::Log(Logger::Error, "IOCP Server couldn't be started");
		// assert
	}
}

IOCPServer::~IOCPServer() {
	closesocket(listenSocket);
	CloseHandle(iocp);
}

bool IOCPServer::initialize(Json::Document& document) {
	Json::Value& app = document["App"];
	if (app.Empty()) {
		SystemLogger::Log(Logger::Error, "\'App\' document is not exist");
		// assert
		return false;
	}

	strcpy_s(ip.data(), ip.size(), app["Server"]["IP"].GetString());
	port = app["Server"]["Port"].GetInt();
	workerThreadCount = app["Server"]["ThreadCount"].GetInt();

	status = ServerStatus::Initialize;
	
	return true;
}

bool IOCPServer::createListenSocket() {
	listenSocket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET) {
		SystemLogger::Log(Logger::Error, "WSASocekt() error!!");
		return false;
	}

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip.data(), &(servAddr.sin_addr));

	int opt = 1;
	setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, 
		(char*)&opt, sizeof(opt));

	int socketError = bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
	if (socketError == SOCKET_ERROR) {
		SystemLogger::Log(Logger::Error, "bind() error!!");
		return false;
	}

	socketError = listen(listenSocket, 5);
	if (socketError == SOCKET_ERROR) {
		SystemLogger::Log(Logger::Error, "listen() error!!");
		return false;
	}

	return true;
}

unsigned int WINAPI IOCPServer::AcceptThread(LPVOID serverPtr) {
	IOCPServer *server = (IOCPServer*)serverPtr;

	while (true) {
		SOCKET acceptSocket = INVALID_SOCKET;
		SOCKADDR_IN recvAddr;
		int addrLen = sizeof(recvAddr);

		acceptSocket = WSAAccept(server->listenSocket, (SOCKADDR*)&recvAddr,
			&addrLen, NULL, 0);
		if (acceptSocket == SOCKET_ERROR) {
			if(server->getStatus() == ServerStatus::Stop) {
				SystemLogger::Log(Logger::Error, "Accept failed");
				break;
			}
		}

		server->onAccept(acceptSocket, recvAddr);

		if(server->getStatus() != ServerStatus::Ready) {
			break;
		}
	}

	return 0;
}

unsigned int WINAPI IOCPServer::WorkerThread(LPVOID serverPtr) {
	IOCPServer *server = (IOCPServer*)serverPtr;

	while (true) {
		IOCPSession *session = nullptr;
		IOBuffer *ioBuffer = nullptr;
		DWORD transferSize;

		BOOL result = GetQueuedCompletionStatus(server->getIOCP(), 
			&transferSize, (PULONG_PTR)&session, (LPOVERLAPPED*)&ioBuffer, INFINITE);
		if (!result) continue;

		if (!session) {
			SystemLogger::Log(Logger::Error, "socket data broken");
			return 0;
		}

		SessionManager& sessionManager = SessionManager::Instance();
		if (transferSize == 0) {
			SystemLogger::Log(Logger::Info, "disconnected client...");
			sessionManager.closeSession(session);
			continue;
		}

		switch (ioBuffer->getType()) {
		case IOType::Write:
			SystemLogger::Log(Logger::Info, "send bytes %d...", transferSize);
			session->onSend((size_t)transferSize);
			continue;

		case IOType::Read: 
			{
				SystemLogger::Log(Logger::Info, "receive bytes %d...", transferSize);
				Package *package = session->onRecv((size_t)transferSize);
				if (package != nullptr)  server->putPackage(package);
			}
			continue;

		case IOType::Error:
			sessionManager.closeSession(session);
			continue;
		}
	}

	return 0;
}

bool IOCPServer::run() {
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, workerThreadCount);
	if (!iocp) {
		SystemLogger::Log(Logger::Error, "CreateIoCompletionPort() error!!");
		return false;
	}

	if (!this->createListenSocket()) {
		SystemLogger::Log(Logger::Error, "CreateListenSocket() error!!");
		return false;
	}

	HANDLE threadArr[10];

	threadArr[0] = (HANDLE)_beginthreadex(NULL, 0, AcceptThread, this, 0, NULL);
	for (int i = 0; i < workerThreadCount; ++i) {
		threadArr[i + 1] = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, this, 0, NULL);
	}
	status = ServerStatus::Ready;

	while (true) {}
	
	return true;
}

void IOCPServer::onAccept(SOCKET accepter, SOCKADDR_IN addrInfo) {
	IOCPSession *session = new IOCPSession();
	if(!session) {
		SystemLogger::Log(Logger::Warning, "session creatation failed");
		return;
	}

	if(!session->onAccept(accepter, addrInfo)) {
		delete session;
		return;
	}

	SessionManager &sessionManager = SessionManager::Instance();
	if(!sessionManager.addSession(session)) {
		delete session;
		return;
	}
	
	HANDLE handle = CreateIoCompletionPort((HANDLE)accepter, this->getIOCP(),
		(ULONG_PTR)session, NULL);
	if(!handle) {
		delete session;
		return;
	}

	SystemLogger::Log(Logger::Info, "new client connected...[%s]",
		session->getClientAddress().c_str());
	session->recvStandBy();
}