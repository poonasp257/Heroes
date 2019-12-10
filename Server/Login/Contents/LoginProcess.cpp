#include "stdafx.h"
#include "LoginProcess.h"

LoginProcess::LoginProcess() {
	//registerPacketProcess(PacketType::AuthLoginRequest, &LoginProcess::AuthLoginRequest);
	//registerPacketProcess(PacketType::AuthRegisterRequest, &LoginProcess::AuthRegisterRequest);
}

LoginProcess::~LoginProcess() {

}

void LoginProcess::AuthLoginRequest(Session *session, Packet *rowPacket) {
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

void LoginProcess::AuthRegisterRequest(Session *session, Packet *rowPacket) {
	/*	Error code
		#1 id is aleady exist...
		#2 id must be contains characters...
		#3 password is too short...
	*/
}