#include "pch.h"

int main() {


	return 0;
}



//#define BUF_SIZE	100
//#define READ		3
//#define WRITE		5
//
//struct PER_HANDLE_DATA {
//	SOCKET clinetSock;
//	SOCKADDR_IN clinetAddr;
//};
//
//struct PER_IO_DATA {
//	OVERLAPPED overlapped;
//	WSABUF wsaBuf;
//	char buffer[BUF_SIZE];
//	int rwMode;
//};

//unsigned int WINAPI EchoThreadMain(LPVOID CompletionPortID);
//void ErrorHandling(const char *message);
//
//int main() {
//	WSADATA wsaData;
//	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
//		ErrorHandling("WSAStartup() error!");
//	}
//
//	HANDLE completionPort;
//	SYSTEM_INFO systemInfo;
//
//	completionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
//	GetSystemInfo(&systemInfo);
//	for (int i = 0; i < systemInfo.dwNumberOfProcessors; ++i) {
//		_beginthreadex(NULL, 0, EchoThreadMain,
//			(LPVOID)completionPort, 0, NULL);
//	}
//	
//	SOCKET serverSock;
//	SOCKADDR_IN serverAddr;
//
//	serverSock = WSASocket(AF_INET, SOCK_STREAM,
//		IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
//	memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = PF_INET;
//	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//	serverAddr.sin_port = htons(6000);
//
//	bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
//	listen(serverSock, SOMAXCONN);
//
//	while (true) {
//		SOCKET clientSock;
//		SOCKADDR_IN clientAddr;
//		int addrLen = sizeof(clientAddr);
//
//		clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &addrLen);
//		
//		PER_IO_DATA *ioInfo;
//		PER_HANDLE_DATA *handleInfo;
//
//		handleInfo = new PER_HANDLE_DATA;
//		handleInfo->clinetSock = clientSock;
//		memcpy(&(handleInfo->clinetAddr), &clientAddr, addrLen);
//
//		CreateIoCompletionPort((HANDLE)clientSock, completionPort, (DWORD)handleInfo, 0);
//
//		ioInfo = new PER_IO_DATA;
//		memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
//		ioInfo->wsaBuf.len = BUF_SIZE;
//		ioInfo->wsaBuf.buf = ioInfo->buffer;
//		ioInfo->rwMode = READ;
//
//		DWORD recvBytes, flags = 0;
//		WSARecv(handleInfo->clinetSock, &(ioInfo->wsaBuf),
//			1, &recvBytes, &flags, &(ioInfo->overlapped), NULL);
//	}
//
//	return 0;
//}
//
//unsigned int WINAPI EchoThreadMain(LPVOID completionPortID) {
//	HANDLE completionPort = (HANDLE)completionPortID;
//	SOCKET sock;
//	DWORD bytesTrans;
//	PER_HANDLE_DATA *handleInfo;
//	PER_IO_DATA *ioInfo;
//	DWORD flags = 0;
//
//	while (true) {
//		GetQueuedCompletionStatus(completionPort, &bytesTrans, (LPDWORD)&handleInfo,
//			(LPOVERLAPPED*)&ioInfo, INFINITE);
//		sock = handleInfo->clinetSock;
//
//		if (ioInfo->rwMode == READ) {
//			if (bytesTrans == 0) {
//				closesocket(sock);
//				delete handleInfo;
//				delete ioInfo;
//				continue;
//			}
//
//			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
//			ioInfo->wsaBuf.len = bytesTrans;
//			ioInfo->rwMode = WRITE;
//			WSASend(sock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);
//
//			ioInfo = new PER_IO_DATA;
//			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
//			ioInfo->wsaBuf.len = BUF_SIZE;
//			ioInfo->wsaBuf.buf = ioInfo->buffer;
//			ioInfo->rwMode = READ;
//			WSARecv(sock, &(ioInfo->wsaBuf), 1, NULL, &flags, &(ioInfo->overlapped), NULL);
//		}
//		else {
//			puts("message sent!");
//			delete ioInfo;
//		}
//	}
//
//	return 0;
//}
//
//void ErrorHandling(const char *message) {
//	fputs(message, stderr);
//	fputc('\n', stderr);
//	exit(1);
//}