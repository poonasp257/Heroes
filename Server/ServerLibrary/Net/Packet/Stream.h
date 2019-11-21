#ifndef STREAM_H
#define STERAM_H

#define SOCKET_BUFSIZE  (1024 * 10)

class Stream {
private:
    size_t offset;
    size_t readOffset;
    std::array<Byte, SOCKET_BUFSIZE> stream;

private:
    template<class T>
    void write(const T& value) {
		int32_t size = sizeof(value);
		if (this->checkWriteBound(size) == false) {
			return;
		}

		memcpy_s((void*)(stream.data() + offset), stream.size() - offset,
			(const void*)&value, size);
		offset += size;
	}

    template<class T>
    void read(T *retVal) {
		size_t size = sizeof(T);
		if (this->checkReadBound(size) == false) {
			return;
		}

		memcpy_s((void*)retVal, size, (void*)(stream.data() + readOffset),
			size);
		readOffset += size;
	}

public:
    Stream();
    Stream(Byte *data, size_t size);
	~Stream();

	Byte* getData() { return stream.data(); }
	void setData(Byte *data, size_t size);
    void operator=(Stream& stream);
    
	size_t getSize() const { return offset; };

    bool checkWriteBound(size_t len);
    bool checkReadBound(size_t len);
    
    //////////////////////////////////Write/////////////////////////////////////////
    template<class T>
	void operator<<(const T& value) {
		this->write(value);
	}

    template<class T>
    void operator<<(const std::vector<T>& value) {
		*this << (int32_t)value.size();
		for (auto i : value) *this << i;
	}

    void operator<<(const std::string& value);
	void operator<<(const ChanelStatus& value);
	void operator<<(const CharacterInfo& value);

	///////////////////////////////////Read///////////////////////////////////////	
    template<class T>
    void operator>>(T *retVal) {
		this->read(retVal);
	}

    template<class T>
    void operator>>(std::vector<T> *retVal) {
		int32_t size;
		*this >> &size;

		for (int32_t i = 0; i < size; ++i) {
			T data;
			*this >> &data;
			retVal->push_back(data);
		}
	}

    void operator>>(std::string *retVal);
	void operator>>(ChanelStatus *retVal);
	void operator>>(CharacterInfo *retVal);
};
#endif