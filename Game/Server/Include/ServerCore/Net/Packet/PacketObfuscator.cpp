#include "stdafx.h"

PacketObfuscator::PacketObfuscator() : 
	obfuscation(std::make_unique<XorObfuscation>()) {

}

PacketObfuscator::~PacketObfuscator() {

}

void PacketObfuscator::encodeHeader(Byte* src) {
	obfuscation->encode(src, 0, sizeof(int32_t));
}

void PacketObfuscator::encodeData(Byte* src, size_t len) {
	obfuscation->encode(src, sizeof(int32_t), len);
}

void PacketObfuscator::decodeHeader(Byte* src) {
	obfuscation->decode(src, 0, sizeof(int32_t));
}

void PacketObfuscator::decodeData(Byte* src, size_t len) {
	obfuscation->decode(src, sizeof(int32_t), len);
}