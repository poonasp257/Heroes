#include "stdafx.h"
#include "Stream.h"


Stream::Stream() : offset(0), read(0), stream({ 0 }) {

}

Stream::Stream(Byte *data, size_t size) 
	: offset(0), read(0), stream({ 0 }) {
	this->SetData(data, size);
}

Stream::~Stream() {

}

void Stream::SetData(Byte *data, size_t size) {
	offset = size;
	memcpy_s((void*)stream.data(), stream.size(),
		(void*)data, size);
}

// write
template<class T>
void Stream::operator<<(const T& value) {

}

// read
template<class T>
void Stream::operator>>(T *retVal) {

}