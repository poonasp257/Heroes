#ifndef CONTENTS_PROCESS_H
#define CONTENTS_PROCESS_H

class ContentsProcess {
private:
	ThreadJobQueue<Package*> *packageQueue;
	std::array<std::unique_ptr<Thread>, SIZE_16> threadPool;

private:
	void initialize(Json::Document& document);
	void run(Package *package);
    void execute();
	void process();

protected:
	typedef void(*PacketProcess)(Session *session, Packet *rowPacket);
	std::unordered_map<PacketType, PacketProcess> processTable;

	void registerPacketProcess(PacketType type, PacketProcess process);

public:
    ContentsProcess();
    ~ContentsProcess();
    
    void putPackage(Package *package);

	static void NotifyTerminal(Session *session, Packet *rowPacket);
};
#endif