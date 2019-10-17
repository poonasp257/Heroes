#ifndef PACKAGE_H
#define PACKGAE_H

class Session;
class Packet;

class Package {
private:
    Session *session;
    Packet  *packet;

public:
    Package(Session *session, Packet *packet);
    ~Package();
};

#endif