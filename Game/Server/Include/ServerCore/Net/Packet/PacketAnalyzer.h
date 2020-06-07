#ifndef PACKET_ANALYZER_H
#define PACKET_ANALYZER_H

class Packet;

class PacketAnalyzer {
public:
    static std::unique_ptr<Packet> Analyzer(const char* rowPacket, size_t size);
};

#endif