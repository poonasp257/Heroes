#ifndef PCH_H
#define PCH_H

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")

#include <ws2tcpip.h>
#include <winsock2.h>
#include <mswsock.h>
#include <mmsystem.h>
#include <ws2spi.h>
#include <mstcpip.h>

#include <windows.h>
#include <iostream>
#include <io.h>
#include <cstdlib>
#include <cstdio>
#include <cstdint>

#include <assert.h>
#include <fcntl.h>
#include <algorithm>
#include <functional>

#include <thread>
#include <mutex>
#include <memory>

#include <string>
#include <tchar.h>

#include <ctime>
#include <chrono>
#include <random>
#include <typeinfo>

#if _DEBUG
#define CONTEXT_SWITCH	Sleep(1)
#else
#define CONTEXT_SWTICH	::SwitchToThread()
#endif

typedef void(*Function)(void *);

#include "./Util/tinyXml/tinyxml.h"

#include "./Util/type.h"
#include "./Util/util.h"

#include "./Util/singleton.h"
#include "./Util/randomMT.h"

#endif