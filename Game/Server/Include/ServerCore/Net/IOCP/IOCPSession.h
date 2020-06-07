#ifndef IOCPSESSION_H
#define IOCPSESSION_H

enum class IOType{
	Read, Write, Error
};

class IOBuffer {
private:
	OVERLAPPED		overlapped;
	IOType			ioType;
	size_t			totalBytes;
	size_t			currentBytes;
	std::array<char, SOCKET_BUFSIZE> buffer;

public:
	IOBuffer();
	IOBuffer(IOType ioType);
	~IOBuffer();
	
	void clear();

	bool needMoreIO(size_t transferSize);	

	int32_t setupTotalBytes();
	size_t getTotalBytes() const { return totalBytes; }

	void setBuffer(Stream& stream);
	char* getBuffer() { return buffer.data(); }
	size_t getBufferSize() const { return buffer.max_size(); }

	IOType getType() { return ioType; }
	void setType(IOType ioType) { this->ioType = ioType; }

	WSABUF getWsaBuf();
	LPWSAOVERLAPPED getOverlapped() { return &overlapped; }
};

class IOCPSession : public Session {
private:
	std::unordered_map<IOType, IOBuffer> ioBuffer;

private:
	void recv(WSABUF wsaBuf);
	bool isRecving(size_t transferSize);
	void send(WSABUF wsaBuf);

public:
	IOCPSession();
	~IOCPSession();

	virtual void onSend(size_t transferSize);
	virtual void sendPacket(const Packet& packet);

	virtual std::unique_ptr<Package> onRecv(size_t transferSize);
	virtual void recvStandBy();
};

#endif