#include "stdafx.h"

XorObfuscation::XorObfuscation() :
	originalKey("heroes"), 
	originalKeyLen(originalKey.length()) {

}

XorObfuscation::~XorObfuscation() {

}

void XorObfuscation::encode(Byte* src, int offset, size_t count) {
	std::vector<Byte> nextKey(originalKey.begin(), originalKey.end());
	int startIdx = offset;
	int endIdx = offset + count;
	int keyIdx = 0;

	for (int i = startIdx; i < endIdx; ++i) {
		src[i] ^= nextKey[keyIdx];
		nextKey[keyIdx++] = src[i];
		if (keyIdx == originalKeyLen) keyIdx = 0;
	}
}

void XorObfuscation::decode(Byte* src, int offset, size_t count) {
	std::vector<Byte> nextKey(originalKey.begin(), originalKey.end());
	int startIdx = offset;
	int endIdx = offset + count;
	int keyIdx = 0;

	for (int i = startIdx; i < endIdx; ++i) {
		std::swap(src[i], nextKey[keyIdx]);
		src[i] ^= nextKey[keyIdx++];
		if (keyIdx == originalKeyLen) keyIdx = 0;
	}
}