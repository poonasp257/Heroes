#include "stdafx.h"
using namespace std;
using namespace filesystem;

FileLogger::FileLogger() : Logger(), path("Log\\") {
	if (!exists(path)) {
		filesystem::create_directory(path);
	}
	
	Json json;
	bool result = json.readFile("config.json");
	if (!result) {
		cout << "File could not be opened!\n";
		// assert
		return;
	}

	Json::Document& document = json.getDocument();
	Json::Value& name = document["App"]["Name"];
	if (name.IsNull()) {
		cout << "\'Name\' document is not exist\n";
		// assert
		return;
	}

	string rename = name.GetString();
	size_t found = rename.find(".log");

	if (found != string::npos) {
		rename = rename.substr(0, found);
	}

	path += rename + "_";
	path += Clock::NowTickToStr(LOG_DATETIME_FORMAT);
	path += ".log";

	fs.open(path.c_str(), ios::out | ios::app);
	if (fs.bad()) {
		cout << "log error, file open fail\n";
		// assert
	}
}

FileLogger::~FileLogger() {
	fs.clear();
	fs.close();
}

void FileLogger::log(Level level, const wchar_t* message, ...) {
	va_list args;
	va_start(args, message);
	this->log(level, message, args);
	va_end(args);
}

void FileLogger::log(Level level, const wchar_t* message, va_list args) {
	wstring text;
	   
	text = L"[" + logTypes[level] + L"]";
	text += L"[" + convertAnsiToUnicode(Clock::NowTickToStr()) + L"]";
	text += L" ";
	text += message;

	fs << text;
	fs.flush();
}