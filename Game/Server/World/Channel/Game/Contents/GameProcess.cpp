#include "stdafx.h"
#include "GameProcess.h"
#include "PlayerManager.h"

GameProcess::GameProcess() {
	registerPacketProcess(PacketType::SearchAccountRequest, &GameProcess::SearchAccountRequest);
	registerPacketProcess(PacketType::DBSearchAccountResponse, &GameProcess::DBSearchAccountResponse);
	registerPacketProcess(PacketType::CreateAccountRequest, &GameProcess::CreateAccountRequest);
	registerPacketProcess(PacketType::DBCreateAccountResponse, &GameProcess::DBCreateAccountResponse);
	registerPacketProcess(PacketType::GetCharacterListRequest, &GameProcess::GetCharacterListRequest);
	registerPacketProcess(PacketType::DBGetCharacterListResponse, &GameProcess::DBGetCharacterListResponse);
	registerPacketProcess(PacketType::ChangeCharacterOrderRequest, &GameProcess::ChangeCharacterOrderRequest);
	registerPacketProcess(PacketType::DBChangeCharacterOrderResponse, &GameProcess::DBChangeCharacterOrderResponse);
	registerPacketProcess(PacketType::CreateCharacterRequest, &GameProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DBCreateCharacterResponse, &GameProcess::DBCreateCharacterResponse);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &GameProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterResponse, &GameProcess::DBDeleteCharacterResponse);
	registerPacketProcess(PacketType::ConnectChannelRequest, &GameProcess::ConnectChannelRequest);
	registerPacketProcess(PacketType::DisconnectChannelRequest, &GameProcess::DisconnectChannelRequest);
	registerPacketProcess(PacketType::NotifyCharacterMovement, &GameProcess::NotifyCharacterMovement);
	registerPacketProcess(PacketType::NotifyCharacterAction, &GameProcess::NotifyCharacterAction);
}

GameProcess::~GameProcess() {

}

void GameProcess::SearchAccountRequest(Session *session, Packet *rowPacket) {
	SearchAccountRequestPacket *packet = dynamic_cast<SearchAccountRequestPacket*>(rowPacket);
	DBSearchAccountRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;
		
	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBSearchAccountResponse(Session *session, Packet *rowPacket) {
	DBSearchAccountResponsePacket *packet = dynamic_cast<DBSearchAccountResponsePacket*>(rowPacket);
	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		SystemLogger::Log(Logger::Error, L"*invalid session id");
		return;
	}

	SearchAccountResponsePacket responsePacket;
	responsePacket.familyName = packet->familyName;
	responsePacket.creatableCharactersCount = packet->creatableCharactersCount;
	responsePacket.errorCode = packet->errorCode;
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::CreateAccountRequest(Session* session, Packet* rowPacket) {
	CreateAccountRequestPacket* packet = dynamic_cast<CreateAccountRequestPacket*>(rowPacket);

	std::wregex pattern(L"(?=^[^0-9])([a-zA-Z°¡-ÆR0-9]{2,10})");
	std::wsmatch matchResult;
	if (!std::regex_match(packet->familyName, matchResult, pattern)) {
		CreateAccountResponsePacket responsePacket;
		responsePacket.errorCode = ErrorCode::BadRequest;

		session->sendPacket(&responsePacket);
		return;
	}
	   	  
	DBCreateAccountRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;
	dbPacket.familyName = packet->familyName;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBCreateAccountResponse(Session* session, Packet* rowPacket) {
	DBCreateAccountResponsePacket* packet = dynamic_cast<DBCreateAccountResponsePacket*>(rowPacket);
	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		SystemLogger::Log(Logger::Error, L"*invalid session id");
		return;
	}
	
	CreateAccountResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;	
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::GetCharacterListRequest(Session* session, Packet* rowPacket) {
	GetCharacterListRequestPacket *packet = dynamic_cast<GetCharacterListRequestPacket*>(rowPacket);
	DBGetCharacterListRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;

	Terminal *terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBGetCharacterListResponse(Session* session, Packet* rowPacket) {
	DBGetCharacterListResponsePacket *packet = dynamic_cast<DBGetCharacterListResponsePacket*>(rowPacket);
	Session *clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		SystemLogger::Log(Logger::Error, L"*invalid session id");
		return;
	}

	GetCharacterListResponsePacket responsePacket;
	responsePacket.characterList = std::move(packet->characterList);
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::ChangeCharacterOrderRequest(Session* session, Packet* rowPacket) {
	ChangeCharacterOrderRequestPacket *packet = dynamic_cast<ChangeCharacterOrderRequestPacket*>(rowPacket);
	DBChangeCharacterOrderRequestPacket dbPacket;
	dbPacket.clientId = session->getId();
	dbPacket.accountId = packet->accountId;
	dbPacket.fromIndex = packet->fromIndex;
	dbPacket.toIndex = packet->toIndex;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(&dbPacket);
}

void GameProcess::DBChangeCharacterOrderResponse(Session* session, Packet* rowPacket) {
	DBChangeCharacterOrderResponsePacket *packet = dynamic_cast<DBChangeCharacterOrderResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		SystemLogger::Log(Logger::Error, L"*invalid session id");
		return;
	}

	ChangeCharacterOrderResponsePacket responsePacket;
	responsePacket.fromIndex = packet->fromIndex;
	responsePacket.toIndex = packet->toIndex;
	clientSession->sendPacket(&responsePacket);
}

void GameProcess::CreateCharacterRequest(Session *session, Packet *rowPacket) {
	CreateCharacterRequestPacket *packet = dynamic_cast<CreateCharacterRequestPacket*>(rowPacket);

	std::wregex pattern(L"(?=^[^0-9])([a-zA-Z°¡-ÆR0-9]{2,10})");
	std::wsmatch matchResult;
	if (!std::regex_match(packet->characterName, matchResult, pattern)) {
		CreateCharacterResponsePacket responsePacket;
		responsePacket.errorCode = ErrorCode::BadRequest;
		session->sendPacket(&responsePacket);
		return;
	}

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
	dbPacket.accountId = packet->accountId;
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

	auto player = PlayerManager::Instance().findByAccountId(packet->playerInfo.accountId);
	if (player != nullptr) {
		SystemLogger::Log(Logger::Warning, L"*aleady registered player: %s", 
			session->getIP().c_str());
		session->onClose();
		return;
	}













	//PlayerManager::Instance().registerPlayer(session->getId(), packet->playerInfo);


	//ConnectChannelResponsePacket responsePacket;
	//responsePacket.playerTable = PlayerManager::Instance().getPlayerTable();
	//session->sendPacket(&responsePacket);

	//NotifyConnectPlayerPacket notifyPacket;
	//notifyPacket.accountId = packet->accountId;
	//notifyPacket.characterInfo = packet->characterInfo;

	//SessionManager::Instance().BroadcastPacket(&notifyPacket);
}

void GameProcess::DisconnectChannelRequest(Session *session, Packet *rowPacket) {
	DisconnectChannelRequestPacket *packet = dynamic_cast<DisconnectChannelRequestPacket*>(rowPacket);
	auto player = PlayerManager::Instance().findBySessionId(session->getId());
	if (player == nullptr) {
		SystemLogger::Log(Logger::Warning, L"*not registered player: %s",
			session->getIP().c_str());
		session->onClose();
		return;
	}

	//PlayerManager::Instance().unregisterPlayer(session->getId());
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