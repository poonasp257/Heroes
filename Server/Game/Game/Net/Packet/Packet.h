#ifndef PACKET_H
#define PACKET_H

class Packet {
protected:
	PacketType type;

public:
	Packet();
	virtual ~Packet();

	PacketType type() const { return type; }

	virtual Serialize() = 0;
	virtual DeSerialize() = 0;
};

#endif