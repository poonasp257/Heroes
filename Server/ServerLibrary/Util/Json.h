#ifndef JSON_H
#define JSON_H

// rapidjson wrapper class
class Json {
private:
	FILE*				fp;
	rapidjson::Document	document;

public:
	using Document = rapidjson::Document;
	using SizeType = rapidjson::SizeType;
	using Value = rapidjson::Value;

public:
	Json();
	~Json();

	bool readFile(const std::string& fileName);
	bool writeFile(const std::string& fileName);
	Document& getDocument() { return document; }
};

#endif