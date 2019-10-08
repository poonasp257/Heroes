#include "stdafx.h"

#define WORKER_THREAD_NUMBER	10
#define SOCKET_BUFSIZE			(1024 * 10)

enum class StreamMode {
	Read,
	Write
};

struct IO_DATA {
	OVERLAPPED	overlapped;
	WSABUF		wsaBuf;
	StreamMode	ioMode;

	int			totalBytes;
	int			currentBytes;
	char		buffer[SOCKET_BUFSIZE];
};

struct SOCKET_DATA {
	SOCKET			socket;
	SOCKADDR_IN		addrInfo;
	char			inAddress[16];
	IO_DATA			ioData;
};

unsigned int WINAPI AcceptThread(LPVOID context);
unsigned int WINAPI WorkerThread(LPVOID context);

SOCKET listenSocket;

int _tmain() {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		_tprintf(_T("WSAStartup() error!!\n"));
		return -1;
	}

	HANDLE iocp;
	iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, WORKER_THREAD_NUMBER);
	if (!iocp) {
		_tprintf(_T("CreateIoCompletionPort() error!!\n"));
		return -1;
	}

	for (int i = 0; i < WORKER_THREAD_NUMBER; ++i) {
		HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, WorkerThread, iocp, 0, NULL);
		CloseHandle(thread);
	}

	listenSocket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, NULL, WSA_FLAG_OVERLAPPED);
	if (listenSocket == INVALID_SOCKET) {
		_tprintf(_T("WSASocekt() error!!\n"));
		return -1;
	}

	SOCKADDR_IN servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(9000);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int socketError = bind(listenSocket, (SOCKADDR*)&servAddr, sizeof(servAddr));
	if (socketError == SOCKET_ERROR) {
		_tprintf(_T("bind() error!!\n"));
		return -1;
	}

	socketError = listen(listenSocket, 5);
	if (socketError == SOCKET_ERROR) {
		_tprintf(_T("listen() error!!\n"));
		return -1;
	}

	AcceptThread(iocp);

	CloseHandle(iocp);
	WSACleanup();
	return 0;
}

unsigned int WINAPI AcceptThread(LPVOID context) {
	HANDLE iocp = (HANDLE)context;

	while (true) {
		SOCKET acceptSocket = INVALID_SOCKET;
		SOCKADDR_IN recvAddr;
		int addrLen = sizeof(recvAddr);

		acceptSocket = WSAAccept(listenSocket, (SOCKADDR*)&recvAddr,
			&addrLen, NULL, 0);
		if (acceptSocket == SOCKET_ERROR) {
			_tprintf(_T("WSAAccept() error!!\n"));
			continue;
		}

		char clientAddr[64];
		inet_ntop(AF_INET, &(recvAddr.sin_addr), clientAddr, _countof(clientAddr));

		SOCKET_DATA *session = new SOCKET_DATA;
		if (!session) {
			_tprintf(_T("memory alloac failed\n"));
			return -1;
		}

		ZeroMemory(session, sizeof(SOCKET_DATA));
		session->socket = acceptSocket;
		strcpy(session->inAddress, clientAddr);

		session->ioData.ioMode = StreamMode::Read;
		session->ioData.totalBytes = sizeof(session->ioData.buffer);
		session->ioData.currentBytes = 0;
		session->ioData.wsaBuf.buf = session->ioData.buffer;
		session->ioData.wsaBuf.len = sizeof(session->ioData.buffer);

		iocp = CreateIoCompletionPort((HANDLE)acceptSocket, iocp, (ULONG_PTR)session, NULL);
		if (!iocp) {
			closesocket(acceptSocket);
			return -1;
		}

		session->socket = acceptSocket;
		IO_DATA ioData = session->ioData;
		DWORD flags = 0;
		DWORD recvBytes;
		DWORD errorCode = WSARecv(acceptSocket, &(ioData.wsaBuf), 1, &recvBytes,
			&flags, &ioData.overlapped, NULL);
		if ((errorCode == SOCKET_ERROR) && (WSAGetLastError() != ERROR_IO_PENDING)) {
			closesocket(session->socket);
		}
	}

	return 0;
}

unsigned int WINAPI WorkerThread(LPVOID context) {
	HANDLE iocp = (HANDLE)context;

	while (true) {
		SOCKET_DATA *session;
		IO_DATA *ioData;
		DWORD trafficSize;

		int result = GetQueuedCompletionStatus(iocp, &trafficSize,
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
		}
	}
}