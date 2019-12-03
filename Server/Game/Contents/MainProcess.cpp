#include "stdafx.h"
#include "MainProcess.h"

std::unordered_map<oid_t, CharacterInfo> MainProcess::playerTable;

MainProcess::MainProcess() {
	registerPacketProcess(PacketType::AuthLoginRequest, &MainProcess::AuthLoginRequest);
	registerPacketProcess(PacketType::AuthRegisterRequest, &MainProcess::AuthRegisterRequest);
	registerPacketProcess(PacketType::ChanelStatusRequest, &MainProcess::ChanelStatusRequest);
	registerPacketProcess(PacketType::AccountInfoRequest, &MainProcess::AccountInfoRequest);
	registerPacketProcess(PacketType::CreateCharacterRequest, &MainProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &MainProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::ConnectChanelRequest, &MainProcess::ConnectChanelRequest);
	registerPacketProcess(PacketType::DisconnectChanelRequest, &MainProcess::DisconnectChanelRequest);
	registerPacketProcess(PacketType::NotifyCharacterMovement, &MainProcess::NotifyCharacterMovement);
	registerPacketProcess(PacketType::NotifyCharacterAction, &MainProcess::NotifyCharacterAction);
}

MainProcess::~MainProcess() {

}

void MainProcess::AuthLoginRequest(Session *session, Packet *rowPacket) {
	AuthLoginRequestPacket *packet = dynamic_cast<AuthLoginRequestPacket*>(rowPacket);

	// DB
	// Magic code...
	std::wstring id[2] = { L"poona", L"test" };
	std::wstring password[2] = { L"1234", L"1234" };
	Int64 accountId[2] = { 1, 2 };
	//////////////////////////////

	AuthLoginResponsePacket responsePacket;
	for (int i = 0; i < 2; ++i) {
		if (id[i].compare(packet->id) == 0
			&& password[i].compare(packet->password) == 0) {
			responsePacket.accountId = accountId[i]; // DB account object id
			responsePacket.errorCode = 0;
			break;
		}
		else {
			responsePacket.errorCode = -1;
		}
	}

	//if (playerTable.find(accountId) != playerTable.end()) {
	//	disconnect...
	//	erase player in playerTable
	//}
	
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
		info.id = i;
		info.traffic = 0; // chanelserver->SessionManager::Instance::getSessionCount..
		info.name = L"CH." + std::to_wstring(i + 1);
		
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
		1. 계정 정보
		가문명 총 캐릭터 수
		
		2.캐릭터 정보
		이름 레벨 직업 위치
		+ 장착 중인 외형, 장비
	*/
	

	AccountInfoResponsePacket responsePacket;
	responsePacket.creatableCharacters = 10;
	CharacterInfo characterInfo;
	for (int i = 0; i < 4; ++i) {
		characterInfo.characterClass = (CharacterClass)(rand() % 4);
		characterInfo.level = rand() % 60;
		characterInfo.familyName = L"펄어비스";
		characterInfo.characterName = L"캐릭터" + std::to_wstring(i + 1);
		characterInfo.location = L"벨리아 마을";

		responsePacket.characterTable.insert(std::make_pair(i, characterInfo));
	}

	session->sendPacket(&responsePacket);
}

void MainProcess::CreateCharacterRequest(Session *session, Packet *rowPacket) {

}

void MainProcess::DeleteCharacterRequest(Session *session, Packet *rowPacket) {
	
}

void MainProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {
	ConnectChanelRequestPacket *packet = dynamic_cast<ConnectChanelRequestPacket*>(rowPacket);
	//packet->chanelId;
	//packet->characterId;

	//1.DB Query packet->characterId....
	//2.session를 제외한 세션들에게 접속한 캐릭 정보 브로드 캐스팅
	//3.session에게 map 정보 보내기
	
	CharacterInfo characterInfo;
	characterInfo.characterId = 0;
	characterInfo.level = 60;
	characterInfo.currentHp = 60;
	characterInfo.currentMp = 60;
	characterInfo.maxHp = 100;
	characterInfo.maxMp = 100;
	characterInfo.exp = 5.157f;
	characterInfo.position = { 130.0f, 21.75f, 30.0f };
	characterInfo.rotation = { 0, 0, 0 };
	characterInfo.characterClass = CharacterClass::Warrior;
	characterInfo.familyName = L"펄어비스";
	characterInfo.characterName = L"캐릭터" + std::to_wstring(playerTable.size() + 1);
	characterInfo.location = L"벨리아 마을";

	auto foundPlayer = playerTable.find(packet->accountId);
	if (foundPlayer == playerTable.end()) {
		playerTable.insert(std::make_pair(packet->accountId, characterInfo));
	}

	ConnectChanelResponsePacket responsePacket;
	responsePacket.playerTable = playerTable;
	session->sendPacket(&responsePacket);

	NotifyNewConnectPacket notifyPacket;
	notifyPacket.accountId = packet->accountId;
	notifyPacket.characterInfo = characterInfo;

	SessionManager::Instance().BroadcastPacket(&notifyPacket);
}

void MainProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {
	DisconnectChanelRequestPacket *packet = dynamic_cast<DisconnectChanelRequestPacket*>(rowPacket);
}

void MainProcess::NotifyCharacterMovement(Session *session, Packet *rowPacket) {
	NotifyCharacterMovementPacket *packet = dynamic_cast<NotifyCharacterMovementPacket*>(rowPacket);
	
	playerTable[packet->accountId].position = packet->movement.position;
	playerTable[packet->accountId].rotation = packet->movement.rotation;

	SessionManager::Instance().BroadcastPacket(packet);
}

void MainProcess::NotifyCharacterAction(Session *session, Packet *rowPacket) {
	NotifyCharacterActionPacket *packet = dynamic_cast<NotifyCharacterActionPacket*>(rowPacket);

	SessionManager::Instance().BroadcastPacket(packet);
}