#ifndef JSON_H
#define JSON_H

class Json {
private:
	using FileReadStream = rapidjson::FileReadStream;
	using FileWriteStream = rapidjson::FileWriteStream;

public:
	using Document = rapidjson::Document;
	using SizeType = rapidjson::SizeType;
	using Value = rapidjson::Value;

public:
	static bool ReadFile(Document& document, const std::string& fileName);
	static bool WriteFile(Document& document, const std::string& fileName);
};

#endif