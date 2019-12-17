#include "stdafx.h"
#include "MainProcess.h"
#include "PlayerManager.h"

MainProcess::MainProcess() {
	registerPacketProcess(PacketType::AuthLoginRequest, &MainProcess::AuthLoginRequest);
	registerPacketProcess(PacketType::DBAuthLoginResponse, &MainProcess::DBAuthLoginResponse);
	registerPacketProcess(PacketType::AuthRegisterRequest, &MainProcess::AuthRegisterRequest);
	registerPacketProcess(PacketType::DBAuthRegisterResponse, &MainProcess::DBAuthRegisterResponse);
	registerPacketProcess(PacketType::ChanelStatusRequest, &MainProcess::ChanelStatusRequest);
	registerPacketProcess(PacketType::AccountInfoRequest, &MainProcess::AccountInfoRequest);
	registerPacketProcess(PacketType::DBAccountInfoResponse, &MainProcess::DBAccountInfoResponse);
	registerPacketProcess(PacketType::CreateCharacterRequest, &MainProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DBCreateCharacterResponse, &MainProcess::DBCreateCharacterResponse);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &MainProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterResponse, &MainProcess::DBDeleteCharacterResponse);
	registerPacketProcess(PacketType::ConnectChanelRequest, &MainProcess::ConnectChanelRequest);
	registerPacketProcess(PacketType::DBConnectChanelResponse, &MainProcess::DBConnectChanelResponse);
	registerPacketProcess(PacketType::DisconnectChanelRequest, &MainProcess::DisconnectChanelRequest);
	registerPacketProcess(PacketType::NotifyCharacterMovement, &MainProcess::NotifyCharacterMovement);
	registerPacketProcess(PacketType::NotifyCharacterAction, &MainProcess::NotifyCharacterAction);
}

MainProcess::~MainProcess() {

}

void MainProcess::AuthLoginRequest(Session *session, Packet *rowPacket) {
	AuthLoginRequestPacket *packet = dynamic_cast<AuthLoginRequestPacket*>(rowPacket);

	DBAuthLoginRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.id = packet->id;
	dbPacket.password = packet->password;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBAuthLoginResponse(Session *session, Packet *rowPacket) {
	DBAuthLoginResponsePacket *packet = dynamic_cast<DBAuthLoginResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	AuthLoginResponsePacket responsePacket;
	responsePacket.accountId = packet->accountId;
	responsePacket.errorCode = packet->errorCode;

	clientSession->sendPacket(&responsePacket);
}

void MainProcess::AuthRegisterRequest(Session *session, Packet *rowPacket) {
	AuthRegisterRequestPacket *packet = dynamic_cast<AuthRegisterRequestPacket*>(rowPacket);

	DBAuthRegisterRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.id = packet->id;
	dbPacket.password = packet->password;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBAuthRegisterResponse(Session *session, Packet *rowPacket) {
	DBAuthRegisterResponsePacket *packet = dynamic_cast<DBAuthRegisterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	AuthRegisterResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;

	clientSession->sendPacket(&responsePacket);
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

	DBAccountInfoRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBAccountInfoResponse(Session *session, Packet *rowPacket) {
	DBAccountInfoResponsePacket *packet = dynamic_cast<DBAccountInfoResponsePacket*>(rowPacket);
	
	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	AccountInfoResponsePacket responsePacket;
	responsePacket.maxCreatableCharacters = packet->maxCreatableCharacters;
	responsePacket.characterList = std::move(packet->characterList);

	clientSession->sendPacket(&responsePacket);
}

void MainProcess::CreateCharacterRequest(Session *session, Packet *rowPacket) {
	CreateCharacterRequestPacket *packet = dynamic_cast<CreateCharacterRequestPacket*>(rowPacket);
	
	DBCreateCharacterRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;
	dbPacket.characterClass = packet->characterClass;
	dbPacket.characterName = packet->characterName;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBCreateCharacterResponse(Session *session, Packet *rowPacket) {
	DBCreateCharacterResponsePacket *packet = dynamic_cast<DBCreateCharacterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	CreateCharacterResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;

	clientSession->sendPacket(&responsePacket);
}

void MainProcess::DeleteCharacterRequest(Session *session, Packet *rowPacket) {
	DeleteCharacterRequestPacket *packet = dynamic_cast<DeleteCharacterRequestPacket*>(rowPacket);

	DBDeleteCharacterRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.characterId = packet->characterId;
	   
	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBDeleteCharacterResponse(Session *session, Packet *rowPacket) {
	DBDeleteCharacterResponsePacket *packet = dynamic_cast<DBDeleteCharacterResponsePacket*>(rowPacket);

	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	DeleteCharacterResponsePacket responsePacket;
	clientSession->sendPacket(&responsePacket);
}

void MainProcess::ConnectChanelRequest(Session *session, Packet *rowPacket) {
	ConnectChanelRequestPacket *packet = dynamic_cast<ConnectChanelRequestPacket*>(rowPacket);
	//packet->chanelId;

	DBConnectChanelRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.characterId = packet->characterId;
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal("DBAgent");
	terminal->sendPacket(&dbPacket);
}

void MainProcess::DBConnectChanelResponse(Session *session, Packet *rowPacket) {
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

void MainProcess::DisconnectChanelRequest(Session *session, Packet *rowPacket) {
	DisconnectChanelRequestPacket *packet = dynamic_cast<DisconnectChanelRequestPacket*>(rowPacket);
}

void MainProcess::NotifyCharacterMovement(Session *session, Packet *rowPacket) {
	NotifyCharacterMovementPacket *packet = dynamic_cast<NotifyCharacterMovementPacket*>(rowPacket);
	
	CharacterInfo *playerInfo = PlayerManager::Instance().getCharacterInfo(session->getId());
	if (!playerInfo) return;

	playerInfo->position = packet->movement.position;
	playerInfo->rotation = packet->movement.rotation;

	SessionManager::Instance().BroadcastPacket(packet);
}

void MainProcess::NotifyCharacterAction(Session *session, Packet *rowPacket) {
	NotifyCharacterActionPacket *packet = dynamic_cast<NotifyCharacterActionPacket*>(rowPacket);

	SessionManager::Instance().BroadcastPacket(packet);
}