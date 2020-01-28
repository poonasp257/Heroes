#ifndef MONSTER_PROCESS_H
#define MONSTER_PROCESS_H

class Package;
class Session;
class Packet;

class MonsterProcess : public ContentsProcess {
public:
	MonsterProcess();
	virtual ~MonsterProcess();

	//static void ChanelStatusRequest(Session* session, Packet* rowPacket);
};
#endif