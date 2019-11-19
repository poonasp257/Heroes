#include "stdafx.h"
#include "MainProcess.h"

MainProcess::MainProcess() {
	registerPacketProcess(PacketType::AuthLoginRequest, &MainProcess::Login);
}

MainProcess::~MainProcess() {

}

void MainProcess::Login(Session *session, Packet *rowPacket) {
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