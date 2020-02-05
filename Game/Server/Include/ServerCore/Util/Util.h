#ifndef UTIL_H
#define UTIL_H

inline std::wstring convertAnsiToUnicode(const std::string& str) {
	int strlen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), NULL, 0);
	std::wstring wstr;
	wstr.resize(strlen);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), &wstr[0], strlen);

	return wstr;
}

inline std::string convertUnicodeToAnsi(const std::wstring& wstr) {
	int strlen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL);
	std::string str;
	str.resize(strlen);
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &str[0], wstr.length(), NULL, NULL);

	return str;
}
#endif