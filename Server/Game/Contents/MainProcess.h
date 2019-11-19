#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class Package;
class Session;
class Packet;

class MainProcess : public ContentsProcess {
public:
	MainProcess();
    ~MainProcess();

	static void Login(Session *session, Packet *rowPacket);
};

#endif