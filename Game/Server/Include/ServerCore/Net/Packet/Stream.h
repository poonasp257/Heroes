#ifndef STREAM_H
#define STERAM_H

class Stream {
private:
    size_t offset;
    size_t readOffset;
    std::array<Byte, SOCKET_BUFSIZE> stream;

private:
    template<typename T>
	void write(const T& value);
    template<typename T>
	void read(T* retVal);

public:
    Stream();
    Stream(Byte* data, size_t size);
	~Stream();

	Byte* getData() { return stream.data(); }
	void setData(Byte* data, size_t size);
    void operator=(Stream& stream);
    
	size_t getSize() const { return offset; };

    bool checkWriteBound(size_t len);
    bool checkReadBound(size_t len);
    
    template<typename T>
	void operator<<(const T& value);
    template<typename T>
	void operator<<(const std::vector<T>& values);
	template<typename T>
	void operator<<(const std::list<T>& values);
	template<typename KEY, typename VALUE>
	void operator<<(const std::vector<std::pair<KEY, VALUE>>& values);
	template<typename KEY, typename VALUE>
	void operator<<(const std::list<std::pair<KEY, VALUE>>& values);
	template<typename KEY, typename VALUE>
	void operator<<(const std::unordered_map<KEY, VALUE>& values);

    void operator<<(const std::string& value);
	void operator<<(const std::wstring& value);
	void operator<<(const Vector3& value);
	void operator<<(const ChannelInfo& value);
	void operator<<(const CharacterInfo& value);
	void operator<<(const PlayerInfo& value);
	void operator<<(const CharacterMovement& value);

    template<typename T> 
	void operator>>(T* retVal);
    template<typename T> 
	void operator>>(std::vector<T>* retVals);
	template<typename T>
	void operator>>(std::list<T>* retVals);
	template<typename KEY, typename VALUE>
	void operator>>(std::vector<std::pair<KEY, VALUE>>* retVals);
	template<typename KEY, typename VALUE>
	void operator>>(std::list<std::pair<KEY, VALUE>>* retVals);
	template<typename KEY, typename VALUE> 
	void operator>>(std::unordered_map<KEY, VALUE>* retVals);

    void operator>>(std::string* retVal);
	void operator>>(std::wstring* retVal);
	void operator>>(Vector3* retVal);
	void operator>>(ChannelInfo* retVal); 
	void operator>>(CharacterInfo* retVal);
	void operator>>(PlayerInfo* retVal);
	void operator>>(CharacterMovement* retVal);
};

#include "Stream.hpp"
#endif