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
	if (err) return false;

	std::array<char, SIZE_256> readBuffer;
	FileReadStream readStream(fp, readBuffer.data(), readBuffer.size());
	bool result = !document.ParseStream(readStream).HasParseError();

	::fclose(fp);

	return result;
}

bool Json::WriteFile(const std::string& fileName) {
	errno_t err = ::fopen_s(&fp, fileName.c_str(), "wb");
	if (err) {
		return false;
	}

	std::array<char, SIZE_256> writeBuffer;
	FileWriteStream writeStream(fp, writeBuffer.data(), writeBuffer.size());
	PrettyWriter<FileWriteStream> writer(writeStream);
	document.Accept(writer);

	::fclose(fp);

	return true;
}