#ifndef TYPE_H
#define TYPE_H

#include <cstdint>

#define SOCKET_BUFSIZE  (1024*  5)

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

using threadId_t = std::thread::id;
using objectId_t = UInt64;

using JsonFileReadStream = rapidjson::FileReadStream;
using JsonFileWriteStream = rapidjson::FileWriteStream;
using JsonDocument = rapidjson::Document;
using JsonSizeType = rapidjson::SizeType;
using JsonValue = rapidjson::Value;

struct IntPoint {
	int x, y;

	IntPoint(int x = 0, int y = 0) : 
		x(x), y(y) {}

	int magnitude() const { return (int)sqrt((x * x) + (y * y)); }
	IntPoint normalized() const {
		IntPoint normalizedPoint(*this);
		normalizedPoint.normalize();
		return normalizedPoint;
	}
	int sqrMagnitude() const { return ((x * x) + (y * y)); }
	int distance(const IntPoint& other) const {
		return IntPoint(other - *this).magnitude();
	}

	void normalize() {
		this->x /= magnitude();
		this->y /= magnitude();
	}

	IntPoint operator+(const IntPoint& rhs) const {
		return IntPoint(x + rhs.x, y + rhs.y);
	}
	IntPoint operator-(const IntPoint& rhs) const {
		return IntPoint(x - rhs.x, y - rhs.y);
	}
	IntPoint operator*(float num) const {
		return IntPoint((int)(x * num), (int)(y * num));
	}
	IntPoint operator/(float num) const {
		return IntPoint((int)(x / num), (int)(y / num));
	}

	IntPoint& operator+=(const IntPoint& rhs) {
		*this = *this + rhs;
		return *this;
	}
	IntPoint& operator-=(const IntPoint& rhs) {
		*this = *this - rhs;
		return *this;
	}
	IntPoint& operator*=(float num) {
		*this = *this * num;
		return *this;
	}
	IntPoint& operator/=(float num) {
		*this = *this / num;
		return *this;
	}

	bool operator!=(const IntPoint& rhs) const {
		return ((x != rhs.x) && (y != rhs.y));
	}
	bool operator==(const IntPoint& rhs) const {
		return ((x == rhs.x) && (y == rhs.y));
	}
};

struct FloatPoint {
	float x, y;

	FloatPoint(float x = 0.0f, float y = 0.0f) :
		x(x), y(y) {}

	float magnitude() const { return sqrt((x * x) + (y * y)); }
	FloatPoint normalized() const {
		FloatPoint normalizedPoint(*this);
		normalizedPoint.normalize();
		return normalizedPoint;
	}
	float sqrMagnitude() const { return ((x * x) + (y * y)); }
	float distance(const FloatPoint& other) const {
		return FloatPoint(other - *this).magnitude();
	}

	void normalize() {
		this->x /= magnitude();
		this->y /= magnitude();
	}
	
	FloatPoint operator+(const FloatPoint& rhs) const {
		return FloatPoint(x + rhs.x, y + rhs.y);
	}
	FloatPoint operator-(const FloatPoint& rhs) const {
		return FloatPoint(x - rhs.x, y - rhs.y);
	}
	FloatPoint operator*(float num) const {
		return FloatPoint(x * num, y * num);
	}
	FloatPoint operator/(float num) const {
		return FloatPoint(x / num, y / num);
	}

	FloatPoint& operator+=(const FloatPoint& rhs) {
		*this = *this + rhs;
		return *this;
	}
	FloatPoint& operator-=(const FloatPoint& rhs) {
		*this = *this - rhs;
		return *this;
	}
	FloatPoint& operator*=(float num) {
		*this = *this * num;
		return *this;
	}
	FloatPoint& operator/=(float num) {
		*this = *this / num;
		return *this;
	}

	bool operator!=(const FloatPoint& rhs) const {
		return ((x != rhs.x) && (y != rhs.y));
	}
	bool operator==(const FloatPoint& rhs) const {
		return ((x == rhs.x) && (y == rhs.y));
	}
};

struct IntVector {
	int x, y, z;

	IntVector(int x = 0, int y = 0, int z = 0) :
		x(x), y(y), z(z) {}

	int magnitude() const { return (int)sqrt((x * x) + (y * y) + (z * z)); }
	IntVector normalized() const {
		IntVector normalizedPoint(*this);
		normalizedPoint.normalize();
		return normalizedPoint;
	}
	int sqrMagnitude() const { return ((x * x) + (y * y) + (z * z)); }
	int distance(const IntVector& other) const {
		return IntVector(other - *this).magnitude();
	}

	void normalize() {
		this->x /= magnitude();
		this->y /= magnitude();
		this->z /= magnitude();
	}
	
	IntVector operator+(const IntVector& rhs) const {
		return IntVector(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	IntVector operator-(const IntVector& rhs) const {
		return IntVector(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	IntVector operator*(float num) const {
		return IntVector((int)(x * num), (int)(y * num), (int)(z * num));
	}
	IntVector operator/(float num) const {
		return IntVector((int)(x / num), (int)(y / num), (int)(z / num));
	}

	IntVector& operator+=(const IntVector& rhs) {
		*this = *this + rhs;
		return *this;
	}
	IntVector& operator-=(const IntVector& rhs) {
		*this = *this - rhs;
		return *this;
	}
	IntVector& operator*=(float num) {
		*this = *this * num;
		return *this;
	}
	IntVector& operator/=(float num) {
		*this = *this / num;
		return *this;
	}

	bool operator!=(const IntVector& rhs) const {
		return ((x != rhs.x) && (y != rhs.y) && (z != rhs.z));
	}
	bool operator==(const IntVector& rhs) const {
		return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
	}
};

struct FloatVector {
	float x, y, z;

	FloatVector(float x = 0.0f, float y = 0.0f, float z = 0.0f) : 
		x(x), y(y), z(z) {}

	float magnitude() const { return  sqrt((x * x) + (y * y) + (z * z)); }
	FloatVector normalized() const {
		FloatVector normalizedPoint(*this);
		normalizedPoint.normalize();
		return normalizedPoint;
	}
	float sqrMagnitude() const { return ((x * x) + (y * y) + (z * z)); }
	float distance(const FloatVector& other) const {
		return FloatVector(other - *this).magnitude();
	}

	void normalize() {
		this->x /= magnitude();
		this->y /= magnitude();
		this->z /= magnitude();
	}

	static FloatVector MoveTowards(const FloatVector& current, const FloatVector& target, float maxDistanceDelta) {
		FloatVector dir = target - current;
		float magnitude = dir.magnitude();
		if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
			return target;
		}

		return current + dir / magnitude * maxDistanceDelta;
	}

	FloatVector operator+(const FloatVector& rhs) const {
		return FloatVector(x + rhs.x, y + rhs.y, z + rhs.z);
	}
	FloatVector operator-(const FloatVector& rhs) const {
		return FloatVector(x - rhs.x, y - rhs.y, z - rhs.z);
	}
	FloatVector operator*(float num) const {
		return FloatVector(x * num, y * num, z * num);
	}
	FloatVector operator/(float num) const {
		return FloatVector(x / num, y / num, z / num);
	}

	FloatVector& operator+=(const FloatVector& rhs) {
		*this = *this + rhs;
		return *this;
	}
	FloatVector& operator-=(const FloatVector& rhs) {
		*this = *this - rhs;
		return *this;
	}
	FloatVector& operator*=(float num) {
		*this = *this * num;
		return *this;
	}
	FloatVector& operator/=(float num) {
		*this = *this / num;
		return *this;
	}

	bool operator!=(const FloatVector& rhs) const {
		return ((x != rhs.x) && (y != rhs.y) && (z != rhs.z));
	}
	bool operator==(const FloatVector& rhs) const {
		return ((x == rhs.x) && (y == rhs.y) && (z == rhs.z));
	}
};

template<typename value_type>
struct BinaryTreeNode {
	std::array<std::unique_ptr<BinaryTreeNode>, 2> children;
	value_type data;
};

template<typename value_type>
struct QuadTreeNode {
	std::array<std::unique_ptr<QuadTreeNode>, 4> children;
	value_type data;
};

template<typename value_type>
struct OcTreeNode {
	std::array<std::unique_ptr<OcTreeNode>, 8> children;
	value_type data;
};
 
//#################################################
//###			the types used in game			###
//#################################################

// enum type
enum class ActionType : UInt16 {
	Roll,
	Attack,
	Hit,
	Die,
	Revive
};

enum class CharacterClassType : UInt16 {
	None,
	Warrior,
	Crusader,
	Archer,
	Assassin,
	Wizard,
	Elementalist
};

enum StatusCode : Byte {
	Success,
	Fail,
	BadRequest,
	Unauthorized,
	Conflict,
};

using Vector2 = FloatPoint;
using Vector3 = FloatVector;

struct ChannelInfo {
	std::wstring name;
	std::wstring ip;
	UInt16		 port;

	ChannelInfo() : port(0) {}
	ChannelInfo(const ChannelInfo& other) = default;
	ChannelInfo(ChannelInfo&& other) = default;

	ChannelInfo& operator=(const ChannelInfo& rhs) = default;
	ChannelInfo& operator=(ChannelInfo&& rhs) = default;
};

struct CharacterInfo {
	objectId_t id;
	std::wstring name;
	CharacterClassType type;
	UInt32 level;
	float exp;
	Int64 currentHp;
	Int64 currentMp;
	Int64 maxHp;
	Int64 maxMp;
	Int64 defense;
	UInt64 damage;
	Vector3 position;
	Vector3 rotation;
	std::wstring location;

	CharacterInfo() : 
		id(0),
		type(CharacterClassType::None),
		level(1), 
		exp(0), 
		currentHp(0), 
		currentMp(0), 
		maxHp(0), 
		maxMp(0),
		defense(0),
		damage(0) {}
};

struct PlayerInfo {
	objectId_t id;
	std::wstring familyName;
	CharacterInfo characterInfo;
	PlayerInfo() : id(0) {}
};

struct CharacterMovement {
	float moveAmount;
	Vector3 direction;
	Vector3 position;

	CharacterMovement() : 
		moveAmount(0.0f) {}
};

struct MonsterInfo {
	objectId_t id;
	objectId_t typeId;
	std::wstring name;
	UInt32 level;
	Int64 currentHp;
	Int64 maxHp;
	UInt32 damage;
	UInt32 defense;
	Vector3 position;
	Vector3 rotation;
	Vector3 originPosition;
	Vector3 originRotation;

	MonsterInfo() :
		id(0),
		typeId(0),
		level(0),
		currentHp(0),
		maxHp(0),
		damage(0),
		defense(0) {}
};

struct MonsterZoneInfo {
	objectId_t id;
	Vector3 position;
	std::vector<MonsterInfo> monsterList;

	MonsterZoneInfo() : 
		id(0) {}
};

#endif