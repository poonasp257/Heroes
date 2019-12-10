#ifndef TERMINALSESSION_H
#define TERMINALSESSION_H

class TerminalSession : public Session {
public:
	TerminalSession();
	virtual ~TerminalSession();

	bool connectTo(const char *ip, int port);
		 
	void onSend(size_t transferSize);
	void sendPacket(Packet *packet);

	Package* onRecv(size_t transferSize);
	void recvStandBy();
};
#endif