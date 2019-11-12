#ifndef PACKET_ANALYZER_H
#define PACKET_ANALYZER_H

class PacketAnalyzer {
public:
    static Packet* Analyzer(const char *rowPacket, size_t size);

};

#endif