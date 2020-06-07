#include "stdafx.h"

Package::Package(std::shared_ptr<Session> session, std::unique_ptr<Packet> packet) : 
    session(std::move(session)), 
    packet(std::move(packet)) {

}

Package::~Package() {

}

Session* Package::getSession() const {
    return session.get();
}

Packet* Package::getPacket() const {
    return packet.get();
}