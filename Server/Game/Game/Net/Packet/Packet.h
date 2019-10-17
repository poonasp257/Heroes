#ifndef PACKET_H
#define PACKET_H

class Packet {
protected:
	PacketType type;

public:
	Packet();
	virtual ~Packet();

	PacketType type() const { return type; }

	virtual serialize() = 0;
	virtual deserialize() = 0;
};

#endif