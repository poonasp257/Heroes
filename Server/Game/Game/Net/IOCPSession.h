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

	bool NeedMoreIO(size_t transferSize);	

	int32_t SetTotalBytes();
	size_t GetTotalBytes() const { return totalBytes; }

	char* GetBuffer() { return buffer.data(); }
	bool SetBuffer(Stream& stream);
	WSABUF CreateWsabuf();
	LPWSAOVERLAPPED GetOvelapped() { return &overlapped; }
};

class IOCPSession : public Session {
private:
	IOBuffer readBuffer;
	IOBuffer writeBuffer;

private:
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