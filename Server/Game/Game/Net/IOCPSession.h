#ifndef IOCPSESSION_H
#define IOCPSESSION_H

#define SOCKET_BUFSIZE (1024 * 10)

class IOBuffer {
	size_t			totalBytes;
	size_t			currentBytes;
	OVERLAPPED		overlapped;
	std::array<char, SOCKET_BUFSIZE> buffer;

public:
	IOBuffer();
	~IOBuffer();

	void Clear();
	
	int32_t SetTotalBytes();
	size_t GetTotalBytes() const;

	char* GetBuffer();
	bool SetBuffer(Stream& stream);
	WSABUF CreateWsabuf();
	LPWSAOVERLAPPED GetOvelapped();
};

class IOCPSession : public Session {
private:
	IOBuffer readBuffer;
	IOBuffer writeBuffer;

private:
	void CheckError(DWORD ret);
	void Recv(WSABUF wsaBuf);
	bool IsRecving(size_t transferSize);
	void Send(WSABUF wsaBuf);

public:
	IOCPSession();
	~IOCPSession();

	virtual void OnSend(size_t transferSize);
	virtual void SendPacket(Packet *packet);

	virtual Package* OnRecv(size_t transferSize);
	virtual void RecvStanBy();
};

#endif