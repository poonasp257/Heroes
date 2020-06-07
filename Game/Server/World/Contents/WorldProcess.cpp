#include "stdafx.h"
#include "WorldProcess.h"
#include "Player/Player.h"
#include "Player/PlayerManager.h"
#include "Player/UserManager.h"
#include "Monster/MonsterZone.h"
#include "Monster/MonsterManager.h"

std::string WorldProcess::authServerAddr = "";

WorldProcess::WorldProcess() {
	const auto& authServerConfig = ConfigManager::Instance().getConfig();
	authServerAddr = authServerConfig["AuthServer"]["IP"].GetString();
	authServerAddr += Format(":%d", authServerConfig["AuthServer"]["Port"].GetInt());

	registerPacketProcess(PacketType::SearchAccountRequest, &WorldProcess::SearchAccountRequest);
	registerPacketProcess(PacketType::DBSearchAccountResponse, &WorldProcess::DBSearchAccountResponse);
	registerPacketProcess(PacketType::CreateAccountRequest, &WorldProcess::CreateAccountRequest);
	registerPacketProcess(PacketType::DBCreateAccountResponse, &WorldProcess::DBCreateAccountResponse);
	registerPacketProcess(PacketType::GetCharacterListRequest, &WorldProcess::GetCharacterListRequest);
	registerPacketProcess(PacketType::DBGetCharacterListResponse, &WorldProcess::DBGetCharacterListResponse);
	registerPacketProcess(PacketType::ChangeCharacterOrderRequest, &WorldProcess::ChangeCharacterOrderRequest);
	registerPacketProcess(PacketType::DBChangeCharacterOrderResponse, &WorldProcess::DBChangeCharacterOrderResponse);
	registerPacketProcess(PacketType::CreateCharacterRequest, &WorldProcess::CreateCharacterRequest);
	registerPacketProcess(PacketType::DBCreateCharacterResponse, &WorldProcess::DBCreateCharacterResponse);
	registerPacketProcess(PacketType::DeleteCharacterRequest, &WorldProcess::DeleteCharacterRequest);
	registerPacketProcess(PacketType::DBDeleteCharacterResponse, &WorldProcess::DBDeleteCharacterResponse);
	registerPacketProcess(PacketType::ConnectChannelRequest, &WorldProcess::ConnectChannelRequest);
	registerPacketProcess(PacketType::DisconnectChannelRequest, &WorldProcess::DisconnectChannelRequest);
	registerPacketProcess(PacketType::WhisperChat, &WorldProcess::WhisperChat);
	registerPacketProcess(PacketType::NotifyChat, &WorldProcess::NotifyChat);
	registerPacketProcess(PacketType::NotifyPlayerMovement, &WorldProcess::NotifyPlayerMovement);
	registerPacketProcess(PacketType::NotifyPlayerAction, &WorldProcess::NotifyPlayerAction);
	registerPacketProcess(PacketType::TakeDamageMonster, &WorldProcess::TakeDamageMonster);
	registerPacketProcess(PacketType::RevivePlayerRequest, &WorldProcess::RevivePlayerRequest);
}

WorldProcess::~WorldProcess() {
	 
}

void WorldProcess::RegisterNewUser(const std::wstring& accessKey, Session* session, objectId_t accountId) {
	UserManager::Instance().registerUser(accessKey, std::make_unique<User>(session->getId(), accountId));
	session->addCloseEvent(L"unregisterUser", [accessKey]() { UserManager::Instance().unregisterUser(accessKey); });
}

void WorldProcess::DBSearchAccountRequest(objectId_t sessionId, objectId_t accountId) {
	DBSearchAccountRequestPacket dbPacket;
	dbPacket.clientId = sessionId;
	dbPacket.accountId = accountId;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::SearchAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const SearchAccountRequestPacket*>(rowPacket);
	std::wstring accessKey = packet->accessKey;

	HttpForm httpForm;
	httpForm.addField(L"accessKey", accessKey);
	HttpRequest httpRequest;
	bool result = httpRequest.post(authServerAddr + "/account/auth", httpForm,
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
					WARNING_FILE_LOG(L"\"%s\" is trying to be inappropriate.", session->getIP().c_str());
					SessionManager::Instance().closeSession(session);
					break;
				}
				case StatusCode::Conflict: {
					std::wstring usingAccessKey = ConvertAnsiToUnicode(responsedData["usingAccessKey"].GetString());
					User* user = UserManager::Instance().find(usingAccessKey);
					if (user != nullptr) {
						INFO_LOG(L"conflict %d session", user->sessionId);
						SessionManager::Instance().closeSession(user->sessionId);
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

void WorldProcess::DBSearchAccountResponse(Session* session, const Packet* rowPacket) {
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

void WorldProcess::CreateAccountRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const CreateAccountRequestPacket*>(rowPacket);
	if (!CheckUsernameFormat(packet->familyName)) {
		CreateAccountResponsePacket responsePacket;
		responsePacket.errorCode = StatusCode::BadRequest;
		session->sendPacket(responsePacket);
		return;
	}

	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBCreateAccountRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.familyName = packet->familyName;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::DBCreateAccountResponse(Session* session, const Packet* rowPacket) {
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

void WorldProcess::GetCharacterListRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const GetCharacterListRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBGetCharacterListRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::DBGetCharacterListResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBGetCharacterListResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) {
		ERROR_LOG(L"*invalid session id");
		return;
	}

	auto& playerManager = PlayerManager::Instance();
	GetCharacterListResponsePacket responsePacket;
	for (auto& character : packet->characterList) {
		auto characterData = playerManager.getCharacterData(character.type, character.level);
		auto newCharacter = character;
		newCharacter.maxHp = characterData.maxHp;
		newCharacter.maxMp = characterData.maxMp;
		newCharacter.defense = characterData.defense;
		newCharacter.damage = characterData.damage;
		responsePacket.characterList.push_back(newCharacter);
	}

	clientSession->sendPacket(responsePacket);
}

void WorldProcess::ChangeCharacterOrderRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const ChangeCharacterOrderRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	DBChangeCharacterOrderRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.fromIndex = packet->fromIndex;
	dbPacket.toIndex = packet->toIndex;

	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::DBChangeCharacterOrderResponse(Session* session, const Packet* rowPacket) {
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

void WorldProcess::CreateCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const CreateCharacterRequestPacket*>(rowPacket);
	if (!CheckUsernameFormat(packet->characterName)) {
		CreateCharacterResponsePacket responsePacket;
		responsePacket.errorCode = StatusCode::BadRequest;
		session->sendPacket(responsePacket);
		return;
	}

	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	auto characterData = PlayerManager::Instance().getCharacterData(packet->classType);
	DBCreateCharacterRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.classType = packet->classType;
	dbPacket.characterName = packet->characterName;
	dbPacket.hp = characterData.maxHp;
	dbPacket.mp = characterData.maxMp;
	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::DBCreateCharacterResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBCreateCharacterResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	CreateCharacterResponsePacket responsePacket;
	responsePacket.errorCode = packet->errorCode;
	clientSession->sendPacket(responsePacket);
}

void WorldProcess::DeleteCharacterRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DeleteCharacterRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}
	
	DBDeleteCharacterRequestPacket dbPacket;
	dbPacket.clientId = user->sessionId;
	dbPacket.accountId = user->accountId;
	dbPacket.characterId = packet->characterId;
	   
	Terminal* terminal = TerminalManager::Instance().getTerminal(L"WorldDB");
	terminal->sendPacket(dbPacket);
}

void WorldProcess::DBDeleteCharacterResponse(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DBDeleteCharacterResponsePacket*>(rowPacket);
	Session* clientSession = SessionManager::Instance().getSession(packet->clientId);
	if (!clientSession) return;

	DeleteCharacterResponsePacket responsePacket;
	clientSession->sendPacket(responsePacket);
}

void WorldProcess::ConnectChannelRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const ConnectChannelRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	PlayerManager::Instance().registerPlayer(session, packet->familyName, packet->characterInfo);
}

void WorldProcess::DisconnectChannelRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const DisconnectChannelRequestPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	//PlayerManager::Instance().unregisterPlayer(packet->playerId);
}

void WorldProcess::WhisperChat(Session* session, const Packet* rowPacket) {
	//auto packet = static_cast<const WhisperChatPacket*>(rowPacket);
	//Player* player = PlayerManager::Instance().find(packet->receiverName);
	//if (player == nullptr) {
	//	WARNING_LOG(L"client %s trying to access invalid key", session->getIP().c_str());
	//	session->
	//}
}

void WorldProcess::NotifyChat(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const NotifyChatPacket*>(rowPacket);
	std::shared_ptr<Player> player = PlayerManager::Instance().find(packet->playerId);
	if (player == nullptr) return;

	player->notifyPlayersInRange(*packet);
	session->sendPacket(*packet);

	INFO_FILE_LOG(L"[%s]:%s", packet->name.c_str(), packet->message.c_str());
}

void WorldProcess::NotifyPlayerMovement(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const NotifyPlayerMovementPacket*>(rowPacket);
	std::shared_ptr<Player> player = PlayerManager::Instance().find(packet->playerId);
	if (player == nullptr) return;

	player->updateMovement(packet->movement);

	PlayerManager::Instance().updatePlayerVisualRange(packet->playerId);
	MonsterManager::Instance().updateVisualRange(player);
	player->notifyMovementInRange();
}

void WorldProcess::NotifyPlayerAction(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const NotifyPlayerActionPacket*>(rowPacket);
	std::shared_ptr<Player> player = PlayerManager::Instance().find(packet->playerId);
	if (player == nullptr) return;

	player->updateMovement(packet->movement);

	PlayerManager::Instance().updatePlayerVisualRange(packet->playerId);
	MonsterManager::Instance().updateVisualRange(player);
	player->notifyActionInRange(packet->actionType);
}

void WorldProcess::TakeDamageMonster(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const TakeDamageMonsterPacket*>(rowPacket);
	User* user = UserManager::Instance().find(packet->accessKey);
	if (user == nullptr) {
		WARNING_FILE_LOG(L"%s trying to access invalid key", session->getIP().c_str());
		return;
	}

	auto monsterZone = MonsterManager::Instance().findMonsterZone(packet->zoneId);
	if (monsterZone == nullptr) {
		WARNING_LOG(L"invalid monster zone id: %d", packet->zoneId);
		return;
	}

	monsterZone->takeDamage(packet->monsterId, packet->playerId);
}

void WorldProcess::RevivePlayerRequest(Session* session, const Packet* rowPacket) {
	auto packet = static_cast<const RevivePlayerRequestPacket*>(rowPacket);
	std::shared_ptr<Player> player = PlayerManager::Instance().find(packet->playerId);
	if (player == nullptr) return;

	RevivePlayerResponsePacket responsePacket;
	session->sendPacket(responsePacket);

	player->revive();
}