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

    std::string id = "poona";
    std::string password = "1234";
    Byte result;

    if(id.compare(packet->id) == 0 
        && password.compare(packet->password) == 0) {
            result = 1;
        }   
    else result = 0;

    AuthLoginResponsePacket responsePacket;
    responsePacket.result = result;

    session->sendPacket(&responsePacket);
}