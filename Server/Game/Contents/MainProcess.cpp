#include "stdafx.h"
#include "MainProcess.h"

MainProcess::MainProcess() {
	registerPacketProcess(PacketType::AuthLoginRequest, &MainProcess::AuthLoginRequest);
	registerPacketProcess(PacketType::AuthRegisterRequest, &MainProcess::AuthRegisterRequest);
	registerPacketProcess(PacketType::ChanelStatusRequest, &MainProcess::ChanelStatusRequest);
	registerPacketProcess(PacketType::AccountInfoRequest, &MainProcess::AccountInfoRequest);
	registerPacketProcess(PacketType::CreateCharacterRequest, &MainProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &MainProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::ConnectChanelRequest, &MainProcess::ConnectChanelRequest);
	registerPacketProcess(PacketType::DisconnectChanelRequest, &MainProcess::DisconnectChanelRequest);
}

MainProcess::~MainProcess() {

}

void MainProcess::AuthLoginRequest(Session *session, Packet *rowPacket) {
    AuthLoginRequestPacket *packet = dynamic_cast<AuthLoginRequestPacket*>(rowPacket);

	// DB
	// Magic code...
    std::wstring id = L"poona";
    std::wstring password = L"1234";
	Int64 accountId = 0;
	//////////////////////////////

	AuthLoginResponsePacket responsePacket;
	if (id.compare(packet->id) == 0
		&& password.compare(packet->password) == 0) {
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
	ChanelInfo info;
	for (int i = 0; i < 10; ++i) {
		info.id = L"CH." + std::to_wstring(i + 1);
		info.traffic = rand() % 5000; // chanelserver->SessionManager::Instance::getSessionCount..
		
		responsePacket.chanelList.push_back(info);
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
	responsePacket.familyName = L"�޾��";
	responsePacket.creatableCharacters = 10;

	CharacterInfo characterInfo;

	for (int i = 0; i < 4; ++i) {
		characterInfo.characterId = i;
		characterInfo.characterClass = (UInt16)rand() % 4;
		characterInfo.level = rand() % 60;
		characterInfo.characterName = L"�����縷" + std::to_wstring(i + 1);
		characterInfo.location = L"������ ����";
		responsePacket.characterList.push_back(characterInfo);
	}

	session->sendPacket(&responsePacket);
}

void MainProcess::CreateCharacterRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::DeleteCharacterRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {
	ConnectChanelRequestPacket *packet = dynamic_cast<ConnectChanelRequestPacket*>(rowPacket);

	ConnectChanelResponsePacket responsePacket;
	responsePacket.status.hp = 100;
	responsePacket.status.mp = 100;
	responsePacket.status.exp = 0;
	responsePacket.status.position = { 10.0f, 10.0f, 10.0f };
	responsePacket.status.rotation = { 0.0f, 0.0f, 0.0f };

	session->sendPacket(&responsePacket);
}

void MainProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {

}