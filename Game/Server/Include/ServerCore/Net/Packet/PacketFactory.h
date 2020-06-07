#ifndef PACKET_FACTORY_H
#define PACKET_FACTORY_H

class Packet;

class PacketFactory {
public:
    static std::unique_ptr<Packet> CreatePacket(PacketType type);
};

#endif