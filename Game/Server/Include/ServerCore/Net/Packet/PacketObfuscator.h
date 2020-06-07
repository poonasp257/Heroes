#ifndef PACKET_OBFUSCATOR_H
#define PACKET_OBFUSCATOR_H

class PacketObfuscator {
private:
	std::unique_ptr<Obfuscation> obfuscation;

private:
	PacketObfuscator();
	~PacketObfuscator();

public:
	PacketObfuscator(const PacketObfuscator&) = delete;
	PacketObfuscator(PacketObfuscator&&) = delete;
	PacketObfuscator& operator=(const PacketObfuscator&) = delete;
	PacketObfuscator& operator=(PacketObfuscator&&) = delete;

	void encodeHeader(Byte* src);
	void encodeData(Byte* src, size_t len);
	void decodeHeader(Byte* src);
	void decodeData(Byte* src, size_t len);

	static auto& Instance() {
		static PacketObfuscator instance;
		return instance;
	}
};
#endif