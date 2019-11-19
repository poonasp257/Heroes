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

void Stream::operator<<(const ChanelStatus& value) {
	*this << value.id;
	*this << value.traffic;
}

void Stream::operator>>(std::string *retVal) {
	int32_t size;
	*this >> &size;
	if(this->checkReadBound(size) == false) { 
		return;
	} 

	char *buf = new char[size + 1];
	memcpy_s((void*)buf, size, (void*)(stream.data() + readOffset), size);
	readOffset += size;
	buf[size] = '\0';

	retVal->clear();
	*retVal = buf;
	
	delete buf;
}

void Stream::operator>>(ChanelStatus *value) {
	*this >> &value->id;
	*this >> &value->traffic;
}