#include "stdafx.h"
#include "GameProcess.h"
#include "UserManager.h"
#include "WorldManager.h"

std::string GameProcess::authServerAddr = "";

GameProcess::GameProcess() {
	const auto& authServerConfig = ConfigManager::Instance().getConfig();
	authServerAddr = authServerConfig["AuthServer"]["IP"].GetString();
	authServerAddr += Format(":%d", authServerConfig["AuthServer"]["Port"].GetInt());

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

void GameProcess::RegisterNewUser(const std::wstring& accessKey, Session* session, objectId_t accountId) {
	UserManager::Instance().registerUser(accessKey, std::make_unique<User>(session->getId(), accountId));
	session->addCloseEvent(L"unregisterUser", [accessKey]() { UserManager::Instance().unregisterUser(accessKey); });
}

void GameProcess::DBSearchAccountRequest(objectId_t sessionId, objectId_t accountId) {
	DBSearchAccountRequestPacket dbPacket;
	dbPacket.clientId = sessionId;
	dbPacket.accountId = accountId;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::SearchAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const SearchAccountRequestPacket*>(rowPacket);
	std::wstring accessKey = packet->accessKey;

	HttpForm httpForm;
	httpForm.addField(L"accessKey", accessKey);
	HttpRequest httpRequest;
	bool result = httpRequest.Post(authServerAddr + "/account/auth", httpForm,
		[&session, accessKey](const std::string& buffer) {
			if (session == nullptr) return;

			Json::Document responsedData;
			responsedData.Parse(buffer.c_str());
			if (!responsedData.HasMember("errorCode")) {
				objectId_t accountId = responsedData["accountId"].GetUint64();
				RegisterNewUser(accessKey, session, accountId);
				DBSearchAccountRequest(session->getId(), accountId);
				return;
			}

			Byte errorCode = responsedData["errorCode"].GetInt();
			switch(errorCode) {
				case StatusCode::Unauthorized: {
					WARNING_LOG(L"\"%s\" is trying to be inappropriate.", session->getIP().c_str());
					SessionManager::Instance().closeSession(session);
					break;
				}
				case StatusCode::Conflict: {
					std::wstring usingAccessKey = ConvertAnsiToUnicode(responsedData["usingAccessKey"].GetString());
					User* user = UserManager::Instance().find(usingAccessKey);
					if (user != nullptr) {
						SessionManager::Instance().closeSession(user->sessionId);
						UserManager::Instance().unregisterUser(usingAccessKey);
					}

					objectId_t accountId = responsedData["accountId"].GetUint64();
					RegisterNewUser(accessKey, session, accountId);
					DBSearchAccountRequest(session->getId(), accountId);
					break;
				}
				default: {
					WARNING_LOG(L"Unknown status code: %d", errorCode);
					break;
				}
			}
		});
	if (!result) {
		SearchAccountResponsePacket responsePacket;
		responsePacket.errorCode = StatusCode::BadRequest;
		session->sendPacket(responsePacket);
	}
}

void GameProcess::DBSearchAccountResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBSearchAccountResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		ERROR_LOG(L"*invalid session id");
		return;
	}

	SearchAccountResponsePacket responsePacket;
	responsePacket.familyName = packet->familyName;
	responsePacket.creatableCharactersCount = packet->creatableCharactersCount;
	responsePacket.errorCode = packet->errorCode;
	clientSession->sendPacket(responsePacket);
}

void GameProcess::CreateAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const CreateAccountRequestPacket*>(rowPacket);
	if (!CheckUsernameFormat(packet->familyName)) {
		CreateAccountResponsePacket responsePacket;
		responsePacket.errorCode = StatusCode::BadRequest;
		session->sendPacket(responsePacket);
		return;
	}

	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBCreateAccountRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.familyName = packet->familyName;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::DBCreateAccountResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateAccountResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		ERROR_LOG(L"*invalid session id");
		return;
	}
	
	CreateAccountResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;	
	clientSession->sendPacket(responsePacket);
}

void GameProcess::GetCharacterListRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const GetCharacterListRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBGetCharacterListRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::DBGetCharacterListResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBGetCharacterListResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		ERROR_LOG(L"*invalid session id");
		return;
	}

	GetCharacterListResponsePacket responsePacket;
	responsePacket.characterList = packet->characterList;
	clientSession->sendPacket(responsePacket);
}

void GameProcess::ChangeCharacterOrderRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const ChangeCharacterOrderRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBChangeCharacterOrderRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.fromIndex = packet->fromIndex;
	dbPacket.toIndex = packet->toIndex;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::DBChangeCharacterOrderResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBChangeCharacterOrderResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		ERROR_LOG(L"*invalid session id");
		return;
	}

	ChangeCharacterOrderResponsePacket responsePacket;
	responsePacket.fromIndex = packet->fromIndex;
	responsePacket.toIndex = packet->toIndex;
	clientSession->sendPacket(responsePacket);
}

void GameProcess::CreateCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const CreateCharacterRequestPacket*>(rowPacket);
	if (!CheckUsernameFormat(packet->characterName)) {
		CreateCharacterResponsePacket responsePacket;
		responsePacket.errorCode = StatusCode::BadRequest;
		session->sendPacket(responsePacket);
		return;
	}

	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBCreateCharacterRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.characterClass = packet->characterClass;
	dbPacket.characterName = packet->characterName;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::DBCreateCharacterResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateCharacterResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	CreateCharacterResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;
	clientSession->sendPacket(responsePacket);
}

void GameProcess::DeleteCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DeleteCharacterRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}
	
	DBDeleteCharacterRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.characterId = packet->characterId;
	   
	Terminal* terminal = TerminalManager::Instance().getTerminal(L"GameDB");
	terminal->sendPacket(dbPacket);
}

void GameProcess::DBDeleteCharacterResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBDeleteCharacterResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	DeleteCharacterResponsePacket responsePacket;
	clientSession->sendPacket(responsePacket);
}

void GameProcess::ConnectChannelRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const ConnectChannelRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	Vector3 position = packet->playerInfo.characterInfo.position;
	Sector* sector = WorldManager::Instance().findSector(position);
	sector->registerPlayer(user->sessionId, packet->playerInfo);

	objectId_t sessionId = user->sessionId;
	session->addCloseEvent(L"unregisterPlayer",
		[sector, sessionId]() {
			INFO_LOG(L"sector %p", sector);
			INFO_LOG(L"user->id: %d", sessionId);
			sector->unregisterPlayer(sessionId);
		});

	ConnectChannelResponsePacket responsePacket;
	responsePacket.playerList = sector->getPlayerList();
	session->sendPacket(responsePacket);
}

void GameProcess::DisconnectChannelRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DisconnectChannelRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	//auto sector = WorldManager::Instance().findSector(user->sessionId);
	//sector->unregisterPlayer(user->sessionId);
}

void GameProcess::NotifyCharacterMovement(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const NotifyCharacterMovementPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
		return;
	}

	//auto sector = WorldManager::Instance().findSector(user->sessionId);
	//sector->updatePlayer(user->sessionId, packet->movement);
}

void GameProcess::NotifyCharacterAction(Session* session, const Packet* rowPacket) {
	/*NotifyCharacterActionPacket* packet = static_cast<NotifyCharacterActionPacket*>(rowPacket);
	SessionManager::Instance().BroadcastPacket(packet);*/
}