#include "stdafx.h"

Stream::Stream() : offset(0), readOffset(0), stream({ 0 }) {

}

Stream::Stream(Byte *data, size_t size) 
	: offset(0), readOffset(0), stream({ 0 }) {
	this->setData(data, size);
}

Stream::~Stream() {

}

void Stream::setData(Byte *data, size_t size) {
	offset = size;
	memcpy_s((void*)stream.data(), stream.size(),
		(void*)data, size);
}

void Stream::operator=(Stream& stream) {
	this->setData(stream.getData(), stream.getSize());
}

bool Stream::checkWriteBound(size_t len) {
	if(offset + len > sizeof(stream)) {
		SystemLogger::Log(Logger::Warning, "stream data over");
		return false;
	}

	return true;
}

bool Stream::checkReadBound(size_t len) {
	if(readOffset + len > offset) {
		SystemLogger::Log(Logger::Warning, "stream has no more buffer");
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

void Stream::operator<<(const ChanelInfo& value) {
	*this << value.id;
	*this << value.traffic;
	*this << value.name;
}

void Stream::operator<<(const CharacterInfo& value) {
	*this << value.characterId;
	*this << value.level;
	*this << value.hp;
	*this << value.mp;
	*this << value.exp;
	*this << value.position;
	*this << value.rotation;
	*this << (UInt16)value.characterClass;
	*this << value.familyName;
	*this << value.characterName;
	*this << value.location;
}

void Stream::operator<<(const CharacterMovement& value) {
	*this << value.moveAmount;
	*this << value.position;
	*this << value.rotation;
}

void Stream::operator>>(std::string *retVal) {
	int32_t len;
	*this >> &len;
	if(this->checkReadBound(len) == false) {
		return;
	} 

	char *buf = new char[len + 1];
	size_t size = len * sizeof(char);

	memcpy_s((void*)buf, size, (void*)(stream.data() + readOffset), size);
	readOffset += size;
	buf[len] = '\0';

	retVal->clear();
	*retVal = buf;
	
	delete buf;
}

void Stream::operator>>(std::wstring *retVal) {
	int32_t len;
	*this >> &len;
	if(this->checkReadBound(len) == false) {
		return;
	} 

	WCHAR *buf = new wchar_t[len + 1];
	size_t size = len * sizeof(wchar_t);
	
	memcpy_s((void*)buf, size, (void*)(stream.data() + readOffset), size);
	readOffset += size;
	buf[len] = L'\0';

	retVal->clear();
	*retVal = buf;
	
	delete buf;
}

void Stream::operator>>(Vector3 *retVal) {
	*this >> &retVal->x;
	*this >> &retVal->y;
	*this >> &retVal->z;
}

void Stream::operator>>(ChanelInfo *retVal) {
	*this >> &retVal->id;
	*this >> &retVal->traffic;
	*this >> &retVal->name;
}

void Stream::operator>>(CharacterInfo *retVal) {
	*this >> &retVal->characterId;
	*this >> &retVal->level;
	*this >> &retVal->hp;
	*this >> &retVal->mp;
	*this >> &retVal->exp;
	*this >> &retVal->position;
	*this >> &retVal->rotation;
	*this >> (UInt16*)&retVal->characterClass;
	*this >> &retVal->familyName;
	*this >> &retVal->characterName;
	*this >> &retVal->location;
}

void Stream::operator>>(CharacterMovement *retVal) {
	*this >> &retVal->moveAmount;
	*this >> &retVal->position;
	*this >> &retVal->rotation;
}