#include "stdafx.h"

Packet* PacketAnalyzer::Analyzer(const char *rowPacket, size_t size) {
    size_t offset = 0;
    PacketType type;

    memcpy_s((void*)&type, sizeof(type), (void*)rowPacket, sizeof(type));
    offset += sizeof(type);

    Packet *packet = PacketFactory::CreatePacket(type);
    if(packet) {
        if(offset < size) {
            Stream stream((BYTE*)(rowPacket + offset), size - offset);
            packet->deSerialize(stream);
        }
    }

    return packet;
}