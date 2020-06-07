template<typename T>
void Stream::write(const T& value) {
	int32_t size = sizeof(value);
	if (this->checkWriteBound(size) == false) {
		return;
	}

	memcpy_s((void*)(stream.data() + offset), stream.size() - offset,
		(const void*)&value, size);
	offset += size;
}

template<typename T>
void Stream::read(T* retVal) {
	size_t size = sizeof(T);
	if (this->checkReadBound(size) == false) {
		return;
	}

	memcpy_s((void*)retVal, size, (void*)(stream.data() + readOffset),
		size);
	readOffset += size;
}

template<typename T>
void Stream::operator<<(const T& value) {
	this->write(value);
}

template<typename T>
void Stream::operator<<(const std::vector<T>& values) {
	*this << (int32_t)values.size();
	for (const auto& value : values) *this << value;
}

template<typename T>
void Stream::operator<<(const std::list<T>& values) {
	*this << (int32_t)values.size();
	for (const auto& value : values) *this << value;
}

template<typename KEY, typename VALUE>
void Stream::operator<<(const std::vector<std::pair<KEY, VALUE>>& values) {
	*this << (int32_t)values.size();
	for (const auto& pair : values) {
		*this << pair.first;
		*this << pair.second;
	}
}

template<typename KEY, typename VALUE>
void Stream::operator<<(const std::list<std::pair<KEY, VALUE>>& values) {
	*this << (int32_t)values.size();
	for (const auto& pair : values) {
		*this << pair.first;
		*this << pair.second;
	}
}

template<typename KEY, typename VALUE>
void Stream::operator<<(const std::unordered_map<KEY, VALUE>& values) {
	*this << (int32_t)values.size();
	for (const auto& pair : values) {
		*this << pair.first;
		*this << pair.second;
	}
}

template<typename T>
void Stream::operator>>(T* retVal) {
	this->read(retVal);
}

template<typename T>
void Stream::operator>>(std::vector<T>* retVals) {
	int32_t size;
	*this >> &size;

	T data;
	for (int32_t i = 0; i < size; ++i) {
		*this >> &data;
		retVals->push_back(data);
	}
}

template<typename T>
void Stream::operator>>(std::list<T>* retVals) {
	int32_t size;
	*this >> &size;

	T data;
	for (int32_t i = 0; i < size; ++i) {
		*this >> &data;
		retVals->push_back(data);
	}
}

template<typename KEY, typename VALUE>
void Stream::operator>>(std::vector<std::pair<KEY, VALUE>>* retVals) {
	int32_t size;
	*this >> &size;

	KEY key;
	VALUE value;
	for (int32_t i = 0; i < size; ++i) {
		*this >> &key;
		*this >> &value;
		retVals->push_back(std::make_pair(key, value));
	}
}

template<typename KEY, typename VALUE>
void Stream::operator>>(std::list<std::pair<KEY, VALUE>>* retVals) {
	int32_t size;
	*this >> &size;

	KEY key;
	VALUE value;
	for (int32_t i = 0; i < size; ++i) {
		*this >> &key;
		*this >> &value;
		retVals->push_back(std::make_pair(key, value));
	}
}

template<typename KEY, typename VALUE>
void Stream::operator>>(std::unordered_map<KEY, VALUE>* retVals) {
	int32_t size;
	*this >> &size;

	KEY key;
	VALUE value;
	for (int32_t i = 0; i < size; ++i) {
		*this >> &key;
		*this >> &value;
		retVals->insert(std::make_pair(key, value));
	}
}