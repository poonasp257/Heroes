#ifndef CONTENTS_PROCESS_H
#define CONTENTS_PROCESS_H

class Session;
class Packet;
class Package;

class ContentsProcess {
private:
	int																threadCount;
	std::vector<std::shared_ptr<Thread>>							threadPool;
	std::unique_ptr<SynchronizedQueue<std::unique_ptr<Package>>>	packageQueue;

private:
    void execute(std::unique_ptr<Package>& package);
	void processThread();

protected:
	using PacketProcess = std::function<void(Session* session, const Packet* rowPacket)>;
	std::unordered_map<PacketType, PacketProcess> processTable;

	void registerPacketProcess(PacketType type, PacketProcess process);

public:
    ContentsProcess();
    ~ContentsProcess();
    
	bool initialize();
	bool run();

    void putPackage(std::unique_ptr<Package>& package);

	static void NotifyTerminal(Session* session, const Packet* rowPacket);
};
#endif