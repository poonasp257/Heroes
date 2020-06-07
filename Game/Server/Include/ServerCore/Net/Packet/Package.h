#ifndef PACKAGE_H
#define PACKGAE_H

class Session;
class Packet;

class Package {
private:
    std::shared_ptr<Session> session;
    std::unique_ptr<Packet> packet;

public:
    Package(std::shared_ptr<Session> session, std::unique_ptr<Packet> packet);
    ~Package();

    Session* getSession() const;
    Packet* getPacket() const;
};

#endif