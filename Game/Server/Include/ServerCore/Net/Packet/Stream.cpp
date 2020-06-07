#include "stdafx.h"

Stream::Stream() : 
	offset(0), 
	readOffset(0), 
	stream({ 0 }) {

}

Stream::Stream(Byte* data, size_t size) 
	: offset(0), readOffset(0), stream({ 0 }) {
	this->setData(data, size);
}

Stream::~Stream() {

}

void Stream::setData(Byte* data, size_t size) {
	offset = size;
	memcpy_s((void*)stream.data(), stream.size(),
		(void*)data, size);
}

void Stream::operator=(Stream& stream) {
	this->setData(stream.getData(), stream.getSize());
}

bool Stream::checkWriteBound(size_t len) {
	if(offset + len > sizeof(stream)) {
		WARNING_LOG(L"stream data over");
		return false;
	}

	return true;
}

bool Stream::checkReadBound(size_t len) {
	if(readOffset + len > offset) {
		WARNING_LOG(L"stream has no more buffer");
		return false;
	}

	return true;
}

void Stream::operator<<(const std::string& value) {
	*this << (int32_t)value.length();
	for(auto i : value) *this << i;
}

void Stream::operator<<(const std::wstring& value) {
	*this << (int32_t)value.length();
	for (auto i : value) *this << i;
}

void Stream::operator<<(const Vector3& value) {
	*this << value.x;
	*this << value.y;
	*this << value.z;
}

void Stream::operator<<(const ChannelInfo& value) {
	*this << value.name;
	*this << value.ip;
	*this << value.port;
}

void Stream::operator<<(const CharacterInfo& value) {
	*this << value.id;
	*this << value.name;
	*this << (UInt16)value.type;
	*this << value.level;
	*this << value.exp;
	*this << value.currentHp;
	*this << value.currentMp;
	*this << value.maxHp;
	*this << value.maxMp;
	*this << value.defense;
	*this << value.damage;
	*this << value.position;
	*this << value.rotation;
	*this << value.location;
}

void Stream::operator<<(const PlayerInfo& value) {
	*this << value.id;
	*this << value.familyName;
	*this << value.characterInfo;
}

void Stream::operator<<(const CharacterMovement& value) {
	*this << value.moveAmount;
	*this << value.direction;
	*this << value.position;
}

void Stream::operator<<(const MonsterInfo& value) {
	*this << value.id;
	*this << value.typeId;
	*this << value.name;
	*this << value.level;
	*this << value.currentHp;
	*this << value.maxHp;
	*this << value.damage;
	*this << value.defense;
	*this << value.position;
	*this << value.rotation;
	*this << value.originPosition;
	*this << value.originRotation;
}

void Stream::operator<<(const MonsterZoneInfo& value) {
	*this << value.id;
	*this << value.position;
	*this << value.monsterList;
}

void Stream::operator>>(std::string* retVal) {
	int32_t len;
	*this >> &len;
	if(this->checkReadBound(len) == false) {
		return;
	} 

	char* buf = new char[len + 1];
	size_t size = len*  sizeof(char);

	memcpy_s((void*)buf, size, (void*)(stream.data() + readOffset), size);
	readOffset += size;
	buf[len] = '\0';

	retVal->clear();
	*retVal = buf;
	
	delete[] buf;
}

void Stream::operator>>(std::wstring* retVal) {
	int32_t len;
	*this >> &len;
	if(this->checkReadBound(len) == false) {
		return;
	} 

	WCHAR* buf = new wchar_t[len + 1];
	size_t size = len*  sizeof(wchar_t);
	
	memcpy_s((void*)buf, size, (void*)(stream.data() + readOffset), size);
	readOffset += size;
	buf[len] = L'\0';

	retVal->clear();
	*retVal = buf;
	
	delete[] buf;
}

void Stream::operator>>(Vector3* retVal) {
	*this >> &retVal->x;
	*this >> &retVal->y;
	*this >> &retVal->z;
}

void Stream::operator>>(ChannelInfo* retVal) {
	*this >> &retVal->name;
	*this >> &retVal->ip;
	*this >> &retVal->port;
}

void Stream::operator>>(CharacterInfo* retVal) {
	*this >> &retVal->id;
	*this >> &retVal->name;
	*this >> (UInt16*)&retVal->type;
	*this >> &retVal->level;
	*this >> &retVal->exp;
	*this >> &retVal->currentHp;
	*this >> &retVal->currentMp;
	*this >> &retVal->maxHp;
	*this >> &retVal->maxMp;
	*this >> &retVal->defense;
	*this >> &retVal->damage;
	*this >> &retVal->position;
	*this >> &retVal->rotation;
	*this >> &retVal->location;
}

void Stream::operator>>(PlayerInfo* retVal) {
	*this >> &retVal->id;
	*this >> &retVal->familyName;
	*this >> &retVal->characterInfo;
}

void Stream::operator>>(CharacterMovement* retVal) {
	*this >> &retVal->moveAmount;
	*this >> &retVal->direction;
	*this >> &retVal->position;
}

void Stream::operator>>(MonsterInfo* retVal) {
	*this >> &retVal->id;
	*this >> &retVal->typeId;
	*this >> &retVal->name;
	*this >> &retVal->level;
	*this >> &retVal->currentHp;
	*this >> &retVal->maxHp;
	*this >> &retVal->damage;
	*this >> &retVal->defense;
	*this >> &retVal->position;
	*this >> &retVal->rotation;
	*this >> &retVal->originPosition;
	*this >> &retVal->originRotation;
}

void Stream::operator>>(MonsterZoneInfo* retVal) {
	*this >> &retVal->id;
	*this >> &retVal->position;
	*this >> &retVal->monsterList;
}