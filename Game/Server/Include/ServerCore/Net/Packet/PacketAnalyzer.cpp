#include "stdafx.h"

std::unique_ptr<Packet> PacketAnalyzer::Analyzer(const char* rowPacket, size_t size) {
    size_t offset = 0;
    PacketType type;
    memcpy_s((void*)&type, sizeof(type), (void*)rowPacket, sizeof(type));
    offset += sizeof(type);

    std::unique_ptr<Packet> packet = PacketFactory::CreatePacket(type);
    if(packet) {
        if(offset < size) {
            Stream stream((BYTE*)(rowPacket + offset), size - offset);
            packet->deSerialize(stream);
        }
    }

    return std::move(packet);
}