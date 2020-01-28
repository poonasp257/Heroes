#include "stdafx.h"
#include "GameProcess.h"
#include "PlayerManager.h"

GameProcess::GameProcess() {
	registerPacketProcess(PacketType::ChanelStatusRequest, &GameProcess::ChanelStatusRequest);
	registerPacketProcess(PacketType::AccountInfoRequest, &GameProcess::AccountInfoRequest);
	registerPacketProcess(PacketType::DBAccountInfoResponse, &GameProcess::DBAccountInfoResponse);
	registerPacketProcess(PacketType::CreateCharacterRequest, &GameProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DBCreateCharacterResponse, &GameProcess::DBCreateCharacterResponse);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &GameProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterResponse, &GameProcess::DBDeleteCharacterResponse);
	registerPacketProcess(PacketType::ConnectChanelRequest, &GameProcess::ConnectChanelRequest);
	registerPacketProcess(PacketType::DBConnectChanelResponse, &GameProcess::DBConnectChanelResponse);
	registerPacketProcess(PacketType::DisconnectChanelRequest, &GameProcess::DisconnectChanelRequest);
	registerPacketProcess(PacketType::NotifyCharacterMovement, &GameProcess::NotifyCharacterMovement);
	registerPacketProcess(PacketType::NotifyCharacterAction, &GameProcess::NotifyCharacterAction);
}

GameProcess::~GameProcess() {

}

void GameProcess::ChanelStatusRequest(Session *session, Packet *rowPacket) {
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

void GameProcess::AccountInfoRequest(Session *session, Packet *rowPacket) {
	AccountInfoRequestPacket *packet = dynamic_cast<AccountInfoRequestPacket*>(rowPacket);

	DBAccountInfoRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBAccountInfoResponse(Session *session, Packet *rowPacket) {
	DBAccountInfoResponsePacket *packet = dynamic_cast<DBAccountInfoResponsePacket*>(rowPacket);
	
	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	AccountInfoResponsePacket responsePacket;
	responsePacket.maxCreatableCharacters = packet->maxCreatableCharacters;
	responsePacket.characterList = std::move(packet->characterList);

	clientSession->sendPacket(&responsePacket);
}

void GameProcess::CreateCharacterRequest(Session *session, Packet *rowPacket) {
	CreateCharacterRequestPacket *packet = dynamic_cast<CreateCharacterRequestPacket*>(rowPacket);
	
	DBCreateCharacterRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;
	dbPacket.characterClass = packet->characterClass;
	dbPacket.characterName = packet->characterName;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBCreateCharacterResponse(Session *session, Packet *rowPacket) {
	DBCreateCharacterResponsePacket *packet = dynamic_cast<DBCreateCharacterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	CreateCharacterResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;

	clientSession->sendPacket(&responsePacket);
}

void GameProcess::DeleteCharacterRequest(Session *session, Packet *rowPacket) {
	DeleteCharacterRequestPacket *packet = dynamic_cast<DeleteCharacterRequestPacket*>(rowPacket);

	DBDeleteCharacterRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.characterId = packet->characterId;
	   
	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBDeleteCharacterResponse(Session *session, Packet *rowPacket) {
	DBDeleteCharacterResponsePacket *packet = dynamic_cast<DBDeleteCharacterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	DeleteCharacterResponsePacket responsePacket;
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {
	ConnectChanelRequestPacket *packet = dynamic_cast<ConnectChanelRequestPacket*>(rowPacket);
	//packet->chanelId;

	DBConnectChanelRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.characterId = packet->characterId;
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBConnectChanelResponse(Session *session, Packet *rowPacket) {
	DBConnectChanelResponsePacket *packet = dynamic_cast<DBConnectChanelResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	PlayerInfo playerInfo;
	playerInfo.accountId = packet->accountId;
	playerInfo.characterInfo = packet->characterInfo;

	PlayerManager::Instance().registerPlayer(clientSession->getId(), playerInfo);

	ConnectChanelResponsePacket responsePacket;
	responsePacket.playerTable = std::move(PlayerManager::Instance().getPlayerTable());
	clientSession->sendPacket(&responsePacket);

	NotifyConnectPlayerPacket notifyPacket;
	notifyPacket.accountId = packet->accountId;
	notifyPacket.characterInfo = packet->characterInfo;

	SessionManager::Instance().BroadcastPacket(&notifyPacket);
}

void GameProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {
	DisconnectChanelRequestPacket *packet = dynamic_cast<DisconnectChanelRequestPacket*>(rowPacket);
}

void GameProcess::NotifyCharacterMovement(Session *session, Packet *rowPacket) {
	NotifyCharacterMovementPacket *packet = dynamic_cast<NotifyCharacterMovementPacket*>(rowPacket);
	
	CharacterInfo *playerInfo = PlayerManager::Instance().getCharacterInfo(session->getId());
	if (!playerInfo) return;

	playerInfo->position = packet->movement.position;
	playerInfo->rotation = packet->movement.rotation;

	SessionManager::Instance().BroadcastPacket(packet);
}

void GameProcess::NotifyCharacterAction(Session *session, Packet *rowPacket) {
	NotifyCharacterActionPacket *packet = dynamic_cast<NotifyCharacterActionPacket*>(rowPacket);

	SessionManager::Instance().BroadcastPacket(packet);
}