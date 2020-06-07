#ifndef OBFUSCATION_H
#define OBFUSCATION_H

class Obfuscation {
public:
	Obfuscation();
	virtual ~Obfuscation();

	virtual void encode(Byte* src, int offset, size_t count) = 0;
	virtual void decode(Byte* src, int offset, size_t count) = 0;
};
#endif