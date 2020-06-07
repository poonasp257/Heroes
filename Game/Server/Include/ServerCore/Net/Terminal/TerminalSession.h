#ifndef TERMINALSESSION_H
#define TERMINALSESSION_H

class TerminalSession : public Session {
public:
	TerminalSession();
	~TerminalSession();

	bool connectTo(const char* ip, int port);
		 
	virtual void onSend(size_t transferSize);
	virtual void sendPacket(const Packet& packet);

	virtual std::unique_ptr<Package> onRecv(size_t transferSize);
	virtual void recvStandBy();
};
#endif