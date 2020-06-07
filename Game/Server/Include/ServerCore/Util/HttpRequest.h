#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

class HttpForm {
private:
	std::string buffer;

public:
	HttpForm() : buffer("") {}
	~HttpForm() {}

	void addField(const std::string& fieldName, uint8_t value) {
		buffer += Format("\"%s\": \"%u\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, int8_t value) {
		buffer += Format("\"%s\": \"%d\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, uint16_t value) {
		buffer += Format("\"%s\": \"%u\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, int16_t value) {
		buffer += Format("\"%s\": \"%d\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, uint32_t value) {
		buffer += Format("\"%s\": \"%u\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, int32_t value) {
		buffer += Format("\"%s\": \"%d\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, uint64_t value) {
		buffer += Format("\"%s\": \"%llu\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, int64_t value) {
		buffer += Format("\"%s\": \"%lld\"", fieldName.c_str(), value);
	}
	void addField(const std::string& fieldName, const std::string& value) {
		buffer += Format("\"%s\": \"%s\"", fieldName.c_str(), value.c_str());
	}
	void addField(const std::wstring& fieldName, const std::wstring& value) {
		std::wstring unicodeStr = Format(L"\"%s\": \"%s\"", fieldName.c_str(), value.c_str());
		buffer += ConvertUnicodeToAnsi(unicodeStr);
	}

	size_t getSize() const { return buffer.length(); }

	std::string getJsonData() const {		
		std::string jsonData = buffer;
		jsonData.insert(0, "{");
		jsonData.push_back('}');
		return jsonData;
	}
};

class HttpRequest {
private:
	CURL* curlContext;
	curl_slist* httpHeaderList;

private:
	static size_t writeCallback(void* ptr, size_t size, size_t count, void* buffer);
	static size_t readCallback(void* ptr, size_t size, size_t count, void* buffer);

public:
	using HttpCallback = std::function<void(const std::string&)>;

public:
	HttpRequest();
	~HttpRequest();

	bool get(const std::string& url, HttpForm form, std::string& buffer);
	bool post(const std::string& url, HttpForm form, HttpCallback callBack);
};
#endif