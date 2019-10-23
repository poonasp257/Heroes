#include "stdafx.h"
#include "Package.h"

Package::Package(Session *session, Packet *packet)
    : session(session), packet(packet) {

}

Package::~Package() {
    session = nullptr; // Session manager가 처리
    delete packet;
}

Session* Package::getSession() {
    return session;
}

Packet* Package::getPacket() {
    return packet;
}