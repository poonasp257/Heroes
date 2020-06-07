#include "stdafx.h"

void Assert(bool condition, LPCWSTR fileName, int lineNo) {
	if (condition) return;

	Server::setState(ServerState::Stop);
	auto message = Format(L"! error, Assertion file: %s, line: %d", fileName, lineNo);
	std::wcout << message;
}