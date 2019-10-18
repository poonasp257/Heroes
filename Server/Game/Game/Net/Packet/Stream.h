#ifndef STREAM_H
#define STERAM_H

class Stream {
private:
    size_t offset;
    size_t read;
    std::array<Byte, SOCKET_BUFSIZE> stream;

public:
    Stream();
    Stream(Byte *data, size_t size);
	~Stream();

	Byte* GetData() { return stream.data(); }
	void SetData(Byte *data, size_t size);

	size_t size() const { return offset; }

    // write
    template<class T>
    void operator<<(const T& value);

    // read
    template<class T>
    void operator>>(T *retVal);    
};

#endif