#include "stdafx.h"
#include "Json.h"

using rapidjson::Document;
using rapidjson::FileReadStream;
using rapidjson::FileWriteStream;
using rapidjson::PrettyWriter;

Json::Json() {

}

Json::~Json() {

}

bool Json::ReadFile(const std::string& fileName) {	
	errno_t err = ::fopen_s(&fp, fileName.c_str(), "rb");
	if (err) {
		return false;
	}

	char readBuffer[65536];
	FileReadStream readStream(fp, readBuffer, _countof(readBuffer));
	bool result = !document.ParseStream(readStream).HasParseError();

	::fclose(fp);

	return result;
}

bool Json::WriteFile(const std::string& fileName) {
	errno_t err = ::fopen_s(&fp, fileName.c_str(), "wb");
	if (err) {
		return false;
	}

	char writeBuffer[65536];
	FileWriteStream writeStream(fp, writeBuffer, _countof(writeBuffer));
	PrettyWriter<FileWriteStream> writer(writeStream);
	document.Accept(writer);

	::fclose(fp);

	return true;
}

inline Document& Json::GetDocument() {
	return document; 
}