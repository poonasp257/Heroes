#ifndef MONSTER_PROCESS_H
#define MONSTER_PROCESS_H

class Package;
class Session;
class Packet;

class MonsterProcess : public ContentsProcess {
public:
	MonsterProcess();
	virtual ~MonsterProcess();

	//static void ChannelStatusRequest(Session* session, Packet* rowPacket);
};
#endif