#ifndef XOR_OBFUSCATION_H
#define XOR_OBFUSCATION_H

class XorObfuscation : public Obfuscation {
private:
	const std::string originalKey;
	const size_t originalKeyLen;

public:
	XorObfuscation();
	~XorObfuscation();

	virtual void encode(Byte* src, int offset, size_t count);
	virtual void decode(Byte* src, int offset, size_t count);
};
#endif