#ifndef IOCPSESSION_H
#define IOCPSESSION_H

#define SOCKET_BUFSIZE (1024 * 10)

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

class IOCPSession : public Session {
public:
	IOCPSession();
	~IOCPSession();
};

#endif