#ifndef LOGIN_PROCESS_H
#define LOGIN_PROCESS_H

class Package;
class Session;
class Packet;

class LoginProcess : public ContentsProcess {
public:
    LoginProcess();
    ~LoginProcess();

    virtual void run(Package *package);

    void Login(Session *session, Packet *rowPacket);
};

#endif