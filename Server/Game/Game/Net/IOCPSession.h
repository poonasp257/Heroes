#ifndef IOCPSESSION_H
#define IOCPSESSION_H

enum class IOType{
	Read, Write, Error
};

// #pragma pack(push, 1)
// union PacketBuffer {
// 	struct {
// 		UInt32 length; 
// 		UInt32 type;
// 		BYTE data[SOCKET_BUFSIZE - 8];
// 	} Segment;

// 	BYTE buffer[SOCKET_BUFSIZE];
// };

class IOBuffer {
	size_t			totalBytes;
	size_t			currentBytes;
	OVERLAPPED		overlapped;
	std::array<char, SOCKET_BUFSIZE> buffer;
	IOType			ioType;

public:
	IOBuffer();
	IOBuffer(IOType ioType);
	~IOBuffer();

	void clear();

	bool needMoreIO(size_t transferSize);	

	uint32_t setupTotalBytes();
	size_t getTotalBytes() const { return totalBytes; }

	bool setBuffer(Stream& stream);
	char* getBuffer() { return buffer.data(); }
	size_t getBufferSize() const { return buffer.max_size(); }

	IOType getType() { return ioType; }
	void setType(IOType ioType) { this->ioType = ioType; }

	WSABUF getWsaBuf();
	LPWSAOVERLAPPED getOverlapped() { return &overlapped; }
};

class IOCPSession : public Session {
private:
	IOBuffer readBuffer;
	IOBuffer writeBuffer;

private:
	void recv(WSABUF wsaBuf);
	bool isRecving(size_t transferSize);
	void send(WSABUF wsaBuf);

public:
	IOCPSession();
	~IOCPSession();

	virtual void onSend(size_t transferSize);
	virtual void sendPacket(Packet *packet);

	virtual Package* onRecv(size_t transferSize);
	virtual void recvStanBy();
};

#endif