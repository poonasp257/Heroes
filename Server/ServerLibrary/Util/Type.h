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
struct ChanelStatus {
	Int32 traffic;
	std::string id; // wstring
};

struct CharacterInfo {
	UInt16 characterClass;
	UInt32 level;
	std::string characterName; // wstring
	std::string location; // zone name
};

#endif