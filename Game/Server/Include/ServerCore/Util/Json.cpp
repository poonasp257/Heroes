#include "stdafx.h"

using rapidjson::PrettyWriter;

bool Json::ReadFile(Document& document, const std::string& fileName) {
	FILE* file = nullptr;
	errno_t err = fopen_s(&file, fileName.c_str(), "rb");
	if (err) {
		std::cerr << "can't read file" << '\n';
		return false;
	}

	std::array<char, SIZE_256> readBuffer;
	FileReadStream readStream(file, readBuffer.data(), readBuffer.size());
	bool result = !document.ParseStream(readStream).HasParseError();
	::fclose(file);

	if (!result) {
		std::cerr << "String is incorrect JSON format" << '\n';
		return false;
	}

	return true;
}

bool Json::WriteFile(Document& document, const std::string& fileName) {
	FILE* file = nullptr;
	errno_t err = ::fopen_s(&file, fileName.c_str(), "wb");
	if (err) {
		std::cerr << "can't write file" << '\n';
		return false;
	}

	std::array<char, SIZE_256> writeBuffer;
	FileWriteStream writeStream(file, writeBuffer.data(), writeBuffer.size());
	PrettyWriter<FileWriteStream> writer(writeStream);
	bool result =  document.Accept(writer);
	::fclose(file);

	if (!result) {
		std::cout << "String is incorrect JSON format" << std::endl;
		return false;
	}

	return true;
}