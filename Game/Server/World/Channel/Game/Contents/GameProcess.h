#ifndef GAME_PROCESS_H
#define GAME_PROCESS_H

class GameProcess : public ContentsProcess {
private:
	static std::string authServerAddr;

public:
	GameProcess();
	~GameProcess();

	static void RegisterNewUser(const std::wstring& accessKey, Session* session, objectId_t accountId);
	static void DBSearchAccountRequest(objectId_t sessionId, objectId_t accountId);

	static void SearchAccountRequest(Session* session, const Packet* rowPacket);
	static void DBSearchAccountResponse(Session* session, const Packet* rowPacket);
	static void CreateAccountRequest(Session* session, const Packet* rowPacket);
	static void DBCreateAccountResponse(Session* session, const Packet* rowPacket);
	static void GetCharacterListRequest(Session* session, const Packet* rowPacket);
	static void ChangeCharacterOrderRequest(Session* session, const Packet* rowPacket);
	static void DBChangeCharacterOrderResponse(Session* session, const Packet* rowPacket);
	static void DBGetCharacterListResponse(Session* session, const Packet* rowPacket);
	static void CreateCharacterRequest(Session* session, const Packet* rowPacket);
	static void DBCreateCharacterResponse(Session* session, const Packet* rowPacket);
	static void DeleteCharacterRequest(Session* session, const Packet* rowPacket);
	static void DBDeleteCharacterResponse(Session* session, const Packet* rowPacket);
	static void ConnectChannelRequest(Session* session, const Packet* rowPacket);
	static void DisconnectChannelRequest(Session* session, const Packet* rowPacket); 
	static void NotifyCharacterMovement(Session* session, const Packet* rowPacket);
	static void NotifyCharacterAction(Session* session, const Packet* rowPacket);
};
#endif