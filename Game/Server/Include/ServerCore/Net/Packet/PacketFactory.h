#ifndef PACKET_FACTORY_H
#define PACKET_FACTORY_H

class PacketFactory {
public:
    static Packet* CreatePacket(PacketType type);

};

#endif