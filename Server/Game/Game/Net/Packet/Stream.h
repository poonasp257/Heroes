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
    void write(const T& value);
    template<class T>
    void read(T *retVal);

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
    
    // write
    template<class T>
    void operator<<(const T& value);

    template<class T>
    void operator<<(const std::vector<T>& value);
    void operator<<(const std::string& value);

    // read
    template<class T>
    void operator>>(T *retVal);  

    template<class T>
    void operator>>(std::vector<T> *retVal);
    void operator>>(std::string *retVal);
};

#endif