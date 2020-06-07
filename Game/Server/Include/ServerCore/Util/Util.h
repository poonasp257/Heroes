#ifndef UTIL_H
#define UTIL_H

inline std::wstring ConvertAnsiToUnicode(const std::string& str) {
	int strlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr;
	wstr.resize(strlen);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], strlen);
	return wstr;
}

inline std::string ConvertUnicodeToAnsi(const std::wstring& wstr) {
	int strlen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
	std::string str;
	str.resize(strlen);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], wstr.length(), NULL, NULL);
	return str;
}

inline bool CheckUsernameFormat(const std::wstring& username) {
	std::wsmatch matchResult;
	std::wregex pattern(L"(?=^[^0-9])([a-zA-Z°¡-ÆR0-9]{2,10})");
	return std::regex_match(username, matchResult, pattern);
}

template<class ... Args>
inline std::string Format(const std::string& fmt, const Args&... args) {
	int len = snprintf(nullptr, 0, fmt.c_str(), args...) + 1;
	if (len <= 0) throw std::invalid_argument("Invalid string format");

	std::unique_ptr<char[]> buffer(new char[len]);
	snprintf(buffer.get(), len, fmt.c_str(), args...);
	return std::string(buffer.get(), buffer.get() + len - 1);
}

template<class ... Args>
inline std::wstring Format(const std::wstring& fmt, const Args&... args) {
	int len = swprintf(nullptr, 0, fmt.c_str(), args...) + 1;
	if (len <= 0) throw std::invalid_argument("Invalid wstring format");

	std::unique_ptr<wchar_t[]> buffer(new wchar_t[len]);
	swprintf(buffer.get(), len, fmt.c_str(), args...);
	return std::wstring(buffer.get(), buffer.get() + len - 1);
}

#endif