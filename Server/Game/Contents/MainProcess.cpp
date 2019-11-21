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
    AuthLoginRequestPacket *packet = dynamic_cast<AuthLoginRequestPacket*>(rowPacket);

	// DB
	// Magic code...
    std::string id = "poona";
    std::string password = "1234";
	Int64 accountId = 0;
	//////////////////////////////

	/*	Error code
		#1 id doesn't exist
		#2 password incorrect
	*/

	AuthLoginResponsePacket responsePacket;
	if (id == packet->id
		&& password == packet->password) {
		responsePacket.accountId = accountId; // DB account object id
		responsePacket.errorCode = 0;
	}
	else {
		responsePacket.errorCode = -1;
	}
	
    session->sendPacket(&responsePacket);
}

void MainProcess::AuthRegisterRequest(Session *session, Packet *rowPacket) {
	/*	Error code
		#1 id is aleady exist...
		#2 id must be contains characters...
		#3 password is too short...
	*/
}

void MainProcess::ChanelStatusRequest(Session *session, Packet *rowPacket) {
	ChanelStatusResponsePacket responsePacket;
	
	// temporary...
	ChanelStatus status;
	for (int i = 0; i < 10; ++i) {
		status.id = "CH-" + std::to_string(i + 1);
		status.traffic = 0; // chanelserver->SessionManager::Instance::getSessionCount..

		responsePacket.chanelList.push_back(status);
	}
	//////////////////////////

	session->sendPacket(&responsePacket);
}

void MainProcess::AccountInfoRequest(Session *session, Packet *rowPacket) {
	AccountInfoRequestPacket *packet = dynamic_cast<AccountInfoRequestPacket*>(rowPacket);

	//searching packet->accountId in db...
	//Get characters information 
	/*
		1. ���� ����
		������ �� ĳ���� ��
		
		2.ĳ���� ����
		�̸� ���� ���� ��ġ
		+ ���� ���� ����, ���
	*/

	AccountInfoResponsePacket responsePacket;
	responsePacket.familyName = "Ƽ������»�";

	CharacterInfo characterInfo;
	characterInfo.characterName = "��������������";
	characterInfo.location = "������ ����";

	for (int i = 0; i < 1; ++i) {
		characterInfo.characterClass = (UInt16)CharacterClass::Warrior;
		characterInfo.level = rand() % 60;
		responsePacket.characterList.push_back(characterInfo);
	}

	session->sendPacket(&responsePacket);
}

void MainProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {

}