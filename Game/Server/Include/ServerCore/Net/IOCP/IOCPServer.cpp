#include "stdafx.h"

IOCPServer::IOCPServer(std::unique_ptr<ContentsProcess> process) : 
	Server(std::move(process)), 
	listenSocket(INVALID_SOCKET), 
	iocp(nullptr) {

}

IOCPServer::~IOCPServer() {
	state = ServerState::Stop;

	DBManager::Instance().stopAll();
	TerminalManager::Instance().stopAll();
	ThreadManager::Instance().joinAll();

	closesocket(listenSocket);
	CloseHandle(iocp);

	INFO_LOG(L"IOCP server closed...");
}

bool IOCPServer::createListenSocket() {
	listenSocket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, 0, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET) {
		ERROR_LOG(L"WSASocekt() error!!");
		return false;
	}

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip.data(), &(servAddr.sin_addr));

	int opt = 1;
	setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));

	int socketError = bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
	if (socketError == SOCKET_ERROR) {
		ERROR_LOG(L"bind() error!!");
		return false;
	}

	socketError = listen(listenSocket, 5);
	if (socketError == SOCKET_ERROR) {
		ERROR_LOG(L"listen() error!!");
		return false;
	}

	INFO_LOG(L"%s Server listening on port %d", name.c_str(), port);
	
	return true;
}

void IOCPServer::acceptThread() {
	while (this->state == ServerState::Running) {
		SOCKET acceptSocket = INVALID_SOCKET;
		SOCKADDR_IN recvAddr;
		int addrLen = sizeof(recvAddr);
		acceptSocket = WSAAccept(this->listenSocket, (SOCKADDR*)&recvAddr, &addrLen, NULL, 0);
		if (acceptSocket == SOCKET_ERROR) {
			if (this->state == ServerState::Stop) {
				ERROR_LOG(L"Accept failed");
				break;
			}
		}

		this->onAccept(acceptSocket, recvAddr);
	}
}

void IOCPServer::workerThread() {
	SessionManager& sessionManager = SessionManager::Instance();
	while (this->state == ServerState::Running) {
		DWORD transferSize;
		IOCPSession* session = nullptr;
		IOBuffer* ioBuffer = nullptr;
		BOOL result = GetQueuedCompletionStatus(this->iocp,
			&transferSize, (PULONG_PTR)&session, (LPOVERLAPPED*)&ioBuffer, INFINITE);
		if (!result) continue;

		if (!session) {
			ERROR_LOG(L"socket data broken");
			return;
		}

		if (transferSize == 0) {
			sessionManager.closeSession(session);
			continue;
		}

		switch (ioBuffer->getType()) {
		case IOType::Write:
			session->onSend((size_t)transferSize);
			break;

		case IOType::Read: {
				auto package = session->onRecv((size_t)transferSize);
				if (package != nullptr)  this->putPackage(package);
			}
			break;

		case IOType::Error:
			sessionManager.closeSession(session);
			break;
		}
	}
}

bool IOCPServer::run() {
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, workerThreadCount);
	if (!iocp) {
		ERROR_LOG(L"CreateIoCompletionPort() error!!");
		return false;
	}

	if (!this->createListenSocket()) {
		ERROR_LOG(L"CreateListenSocket() error!!");
		return false;
	}

	if (!contentsProcess->initialize()) {
		ERROR_LOG(L"Contents Process initialized failed");
		return false;
	}
	if (!TerminalManager::Instance().initialize(shared_from_this())) {
		ERROR_LOG(L"Terminal Manager initialized failed");
		return false;
	}

	state = ServerState::Running;
	threadPool.push_back(MAKE_THREAD(IOCPServer, acceptThread));
	for (int i = 0; i < workerThreadCount; ++i) {
		threadPool.push_back(MAKE_THREAD(IOCPServer, workerThread));
	}

	if (!contentsProcess->run()) {
		ERROR_LOG(L"Contents Process initialized failed");
		return false;
	}
	if (!TerminalManager::Instance().run()) {
		ERROR_LOG(L"Terminal Manager couldn't start");
		return false;
	}

	while (state == ServerState::Running) Sleep(1);

	return true;
}

void IOCPServer::onAccept(SOCKET accepter, SOCKADDR_IN addrInfo) {
	std::shared_ptr<IOCPSession> session = std::make_shared<IOCPSession>();
	session->onAccept(accepter, addrInfo);

	SessionManager& sessionManager = SessionManager::Instance();
	if (!sessionManager.addSession(session)) return;

	HANDLE handle = CreateIoCompletionPort((HANDLE)accepter, this->getIOCP(),
		(ULONG_PTR)session.get(), NULL);
	if (!handle) {
		WARNING_LOG(L"! CreateIoCompletionPort() error");
		sessionManager.closeSession(session.get());
		return;
	}

	session->recvStandBy();
	INFO_LOG(L"new client connected...[%s]", session->getIP().c_str());
}