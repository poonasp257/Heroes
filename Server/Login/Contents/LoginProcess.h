#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class Package;
class Session;
class Packet;

class LoginProcess : public ContentsProcess {
public:
	LoginProcess();
	virtual ~LoginProcess();

	static void AuthLoginRequest(Session *session, Packet *rowPacket);
	static void AuthRegisterRequest(Session *session, Packet *rowPacket);
};

#endif