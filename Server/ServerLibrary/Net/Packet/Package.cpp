#include "stdafx.h"

Package::Package(Session *session, Packet *packet)
    : session(session), packet(packet) {

}

Package::~Package() {
    session = nullptr;
    delete packet;
}

Session* Package::getSession() {
    return session;
}

Packet* Package::getPacket() {
    return packet;
}