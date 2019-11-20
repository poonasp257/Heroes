#include "stdafx.h"
#include "MainProcess.h"

MainProcess::MainProcess() {
	registerPacketProcess(PacketType::AuthLoginRequest, &MainProcess::AuthLoginRequest);
	registerPacketProcess(PacketType::AuthRegisterRequest, &MainProcess::AuthRegisterRequest);
	registerPacketProcess(PacketType::ChanelStatusRequest, &MainProcess::ChanelStatusRequest);
	registerPacketProcess(PacketType::ConnectChanelRequest, &MainProcess::ConnectChanelRequest);
	registerPacketProcess(PacketType::DisconnectChanelRequest, &MainProcess::DisconnectChanelRequest);
	registerPacketProcess(PacketType::AccountInfoRequest, &MainProcess::AccountInfoRequest);
}

MainProcess::~MainProcess() {

}

void MainProcess::AuthLoginRequest(Session *session, Packet *rowPacket) {
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

void MainProcess::AuthRegisterRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::ChanelStatusRequest(Session *session, Packet *rowPacket) {
	ChanelStatusResponsePacket packet;
	ChanelStatus status;
	status.id = "Hidel-1";
	status.traffic = SessionManager::Instance().getConnectionCount();

	packet.chanelList.push_back(status);
	packet.chanelList.push_back(status);
	session->sendPacket(&packet);
}

void MainProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::AccountInfoRequest(Session *session, Packet *rowPacket) {

}