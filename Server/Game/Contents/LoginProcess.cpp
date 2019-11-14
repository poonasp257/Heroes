#include "stdafx.h"
#include "LoginProcess.h"

LoginProcess::LoginProcess() {
    
}

LoginProcess::~LoginProcess() {

}

void LoginProcess::run(Package *package) {
    Session *session = package->getSession();
    Packet *packet = package->getPacket();

    switch(packet->type()) {
        case PacketType::AuthLoginRequest:
            Login(session, packet);
            break;
    }    
}

void LoginProcess::Login(Session *session, Packet *rowPacket) { 
    AuthLoginRequestPacket *packet = (AuthLoginRequestPacket*)rowPacket;

	// DB
	// Magic code...
    std::string id = "poona";
    std::string password = "1234";
	//////////////////////////////

	AuthLoginResponsePacket responsePacket;
	responsePacket.success = (id == packet->id) && (password == packet->password);

    session->sendPacket(&responsePacket);
}