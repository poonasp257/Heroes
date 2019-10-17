#include "stdafx.h"
#include "IOCPServer.h"

IOCPServer::IOCPServer() : Server("IOCPServer"),
	listenSocket(INVALID_SOCKET), iocp(nullptr) {
	bool result = this->Initialize(json.GetDocument());
	if(!result) {
		SystemLogger::Log("IOCP Server couldn't be started", Logger::Error);
		// assert
	}
}

IOCPServer::~IOCPServer() {
	closesocket(listenSocket);
	CloseHandle(iocp);
}

bool IOCPServer::Initialize(Json::Document& document) {
	Json::Value& root = document["root"];
	//if (root.Empty()) {
	//	std::cerr << "\'root\' document is not exist.\n";
	//	return;
	//}

	strcpy_s(ip.data(), root["IP"].GetString());
	port = root["Port"].GetInt();
	workerThreadCount = root["ThreadCount"].GetInt();

	status = ServerStatus::Initialize;
}

bool IOCPServer::CreateListenSocket() {
	listenSocket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET) {
		_tprintf(_T("WSASocekt() error!!\n"));
		return false;
	}

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &(servAddr.sin_addr));

	int socketError = bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
	if (socketError == SOCKET_ERROR) {
		_tprintf(_T("bind() error!!\n"));
		return false;
	}

	socketError = listen(listenSocket, 5);
	if (socketError == SOCKET_ERROR) {
		_tprintf(_T("listen() error!!\n"));
		return false;
	}

	return true;
}

unsigned int WINAPI IOCPServer::AcceptThread(LPVOID serverPtr) {
	IOCPServer *server = static_cast<IOCPServer*>(serverPtr);

	while (true) {
		//SOCKET acceptSocket = INVALID_SOCKET;
		//SOCKADDR_IN recvAddr;
		//int addrLen = sizeof(recvAddr);

		//acceptSocket = WSAAccept(server->listenSocket, (SOCKADDR*)&recvAddr,
		//	&addrLen, NULL, 0);
		//if (acceptSocket == SOCKET_ERROR) {
		//	_tprintf(_T("WSAAccept() error!!\n"));
		//	continue;
		//}

		//// IOCPSession
		//char clientAddr[64];
		//inet_ntop(AF_INET, &(recvAddr.sin_addr), clientAddr, _countof(clientAddr));

		//SOCKET_DATA *session = new SOCKET_DATA;
		//if (!session) {
		//	_tprintf(_T("memory alloac failed\n"));
		//	return -1;
		//}

		//ZeroMemory(session, sizeof(SOCKET_DATA));
		//session->socket = acceptSocket;
		//strcpy(session->inAddress, clientAddr);

		//session->ioData.ioMode = StreamMode::Read;
		//session->ioData.totalBytes = sizeof(session->ioData.buffer);
		//session->ioData.currentBytes = 0;
		//session->ioData.wsaBuf.buf = session->ioData.buffer;
		//session->ioData.wsaBuf.len = sizeof(session->ioData.buffer);

		//server->iocp = CreateIoCompletionPort((HANDLE)acceptSocket, server->iocp, (ULONG_PTR)session, NULL);
		//if (!server->iocp) {
		//	closesocket(acceptSocket);
		//	return -1;
		//}

		//session->socket = acceptSocket;
		//IO_DATA ioData = session->ioData;
		//DWORD flags = 0;
		//DWORD recvBytes;
		//DWORD errorCode = WSARecv(acceptSocket, &(ioData.wsaBuf), 1, &recvBytes,
		//	&flags, &ioData.overlapped, NULL);
		//if ((errorCode == SOCKET_ERROR) && (WSAGetLastError() != ERROR_IO_PENDING)) {
		//	closesocket(session->socket);
		//}
	}

	return 0;
}

unsigned int WINAPI IOCPServer::WorkerThread(LPVOID serverPtr) {
	IOCPServer *server = static_cast<IOCPServer*>(serverPtr);

	while (true) {
	/*	SOCKET_DATA *session;
		IO_DATA *ioData;
		DWORD trafficSize;

		int result = GetQueuedCompletionStatus(server->iocp, &trafficSize,
			(PULONG_PTR)&session, (LPOVERLAPPED*)&ioData, INFINITE);
		if (!result) {
			_tprintf(_T(""));
			continue;
		}

		if (!session) {
			_tprintf(_T("socket data broken\n"));
			return 0;
		}

		if (trafficSize == 0) {
			_tprintf(_T("disconnected client..."));
			closesocket(session->socket);
			continue;
		}

		ioData->currentBytes += trafficSize;
		DWORD flags = 0;

		switch (ioData->ioMode) {
		case StreamMode::Write:
			ioData->wsaBuf.buf[trafficSize] = '\0';
			_tprintf(L"0 send message: %s\n", ioData->wsaBuf.buf);
			break;
		case StreamMode::Read:
			ioData->ioMode = StreamMode::Write;
			ioData->wsaBuf.len = trafficSize;
			flags = 0;

			DWORD sendBytes;
			DWORD errorCode = WSASend(session->socket, &ioData->wsaBuf, 1, &sendBytes,
				flags, &ioData->overlapped, NULL);

			if ((errorCode == SOCKET_ERROR) && (WSAGetLastError() != ERROR_IO_PENDING)) {
				closesocket(session->socket);
				_tprintf(_T("error code = %d\n"), errorCode);
			}

			ioData->wsaBuf.buf[trafficSize] = '\0';
			_tprintf(_T("@ recv client message: %s\n"), ioData->wsaBuf.buf);

			ioData->wsaBuf.len = SOCKET_BUFSIZE;
			ZeroMemory(ioData->buffer, sizeof(ioData->buffer));

			ioData->ioMode = StreamMode::Read;
			DWORD recvBytes;
			errorCode = WSARecv(session->socket, &ioData->wsaBuf, 1, &recvBytes,
				&flags, &ioData->overlapped, NULL);
			if ((errorCode == SOCKET_ERROR) && (WSAGetLastError() != ERROR_IO_PENDING)) {
				closesocket(session->socket);
				_tprintf(_T("error code = %d\n"), errorCode);
			}

			break;
		}*/
	}
}

bool IOCPServer::Run() {
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, workerThreadCount);
	if (!iocp) {
		_tprintf(_T("CreateIoCompletionPort() error!!\n"));
		return false;
	}

	this->CreateListenSocket();

	for (int i = 0; i < workerThreadCount; ++i) {
		HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, this, 0, NULL);
		CloseHandle(thread);
	}

	status = ServerStatus::Ready;

	AcceptThread(this); // 수정 할 것
}

void IOCPServer::OnAccept(SOCKET accepter, SOCKADDR_IN addrInfo) {
	// Session 처리
}