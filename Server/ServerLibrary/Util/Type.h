#ifndef TYPE_H
#define TYPE_H

#include <cstdint>

#define SIZE_8			8
#define SIZE_16			16
#define SIZE_64			64
#define SIZE_128		128
#define SIZE_256		256
#define SIZE_1024		1024
#define SIZE_4096		4096
#define SIZE_8192		8192

using Byte = unsigned char;
using Char = char;
using Int16 = int16_t;
using UInt16 = uint16_t;
using Int32 = int32_t;
using UInt32 = uint32_t;
using Int64 = int64_t;
using UInt64 = uint64_t;
using Float = float;

using threadId = std::thread::id;

// enum type
enum class CharacterClass : UInt16 {
	Warrior, 
	Archer, 
	Assassin, 
	Mage
};

// struct in game...
struct Vector3 {
	float x, y, z;

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
};

struct ChanelInfo {
	Int32 traffic;
	std::wstring id; // wstring
};

struct CharacterInfo {
	UINT64 characterId;
	UInt16 characterClass;
	UInt32 level;
	std::wstring characterName; // wstring
	std::wstring location; // zone name
};

struct CharacterStatus {
	Int64 hp;
	Int64 mp;
	Int64 exp;
	Vector3 position;
	Vector3 rotation;
};

#endif