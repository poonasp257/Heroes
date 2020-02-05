#include "stdafx.h"
#include "GameProcess.h"
#include "PlayerManager.h"

GameProcess::GameProcess() {
	registerPacketProcess(PacketType::AccountInfoRequest, &GameProcess::AccountInfoRequest);
	registerPacketProcess(PacketType::DBAccountInfoResponse, &GameProcess::DBAccountInfoResponse);
	registerPacketProcess(PacketType::CreateCharacterRequest, &GameProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DBCreateCharacterResponse, &GameProcess::DBCreateCharacterResponse);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &GameProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterResponse, &GameProcess::DBDeleteCharacterResponse);
	registerPacketProcess(PacketType::ConnectChannelRequest, &GameProcess::ConnectChannelRequest);
	registerPacketProcess(PacketType::DBConnectChannelResponse, &GameProcess::DBConnectChannelResponse);
	registerPacketProcess(PacketType::DisconnectChannelRequest, &GameProcess::DisconnectChannelRequest);
	registerPacketProcess(PacketType::NotifyCharacterMovement, &GameProcess::NotifyCharacterMovement);
	registerPacketProcess(PacketType::NotifyCharacterAction, &GameProcess::NotifyCharacterAction);
}

GameProcess::~GameProcess() {

}

void GameProcess::AccountInfoRequest(Session *session, Packet *rowPacket) {
	AccountInfoRequestPacket *packet = dynamic_cast<AccountInfoRequestPacket*>(rowPacket);

	DBAccountInfoRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
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

	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
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
	   
	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBDeleteCharacterResponse(Session *session, Packet *rowPacket) {
	DBDeleteCharacterResponsePacket *packet = dynamic_cast<DBDeleteCharacterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	DeleteCharacterResponsePacket responsePacket;
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::ConnectChannelRequest(Session *session, Packet *rowPacket) {
	ConnectChannelRequestPacket *packet = dynamic_cast<ConnectChannelRequestPacket*>(rowPacket);

	DBConnectChannelRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.characterId = packet->characterId;
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBConnectChannelResponse(Session *session, Packet *rowPacket) {
	DBConnectChannelResponsePacket *packet = dynamic_cast<DBConnectChannelResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	PlayerInfo playerInfo;
	playerInfo.accountId = packet->accountId;
	playerInfo.characterInfo = packet->characterInfo;

	PlayerManager::Instance().registerPlayer(clientSession->getId(), playerInfo);

	ConnectChannelResponsePacket responsePacket;
	responsePacket.playerTable = std::move(PlayerManager::Instance().getPlayerTable());
	clientSession->sendPacket(&responsePacket);

	NotifyConnectPlayerPacket notifyPacket;
	notifyPacket.accountId = packet->accountId;
	notifyPacket.characterInfo = packet->characterInfo;

	SessionManager::Instance().BroadcastPacket(&notifyPacket);
}

void GameProcess::DisconnectChannelRequest(Session *session, Packet *rowPacket) {
	DisconnectChannelRequestPacket *packet = dynamic_cast<DisconnectChannelRequestPacket*>(rowPacket);
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