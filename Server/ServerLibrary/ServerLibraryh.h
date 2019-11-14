#ifndef SERVERLIBRARY_H
#define SERVERLIBRARY_H

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <process.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <memory>

#include <algorithm>
#include <string>
#include <array>
#include <list>
#include <queue>
#include <map>

#include <ctime>
#include <chrono>

using namespace std::experimental;

#include "Include/rapidjson/document.h"
#include "Include/rapidjson/filereadstream.h"
#include "Include/rapidjson/filewritestream.h"
#include "Include/rapidjson/prettywriter.h"

#include "Util/Type.h"
#include "Util/Json.h"
#include "Util/Singleton.h"
#include "Util/Clock.h"
#include "Util/Logger.h"

#include "Net/Packet/Stream.h"
#include "Net/Packet/PacketType.h"
#include "Net/Packet/Packet.h"
#include "Net/Packet/PacketAnalyzer.h"
#include "Net/Packet/PacketFactory.h"
#include "Net/Packet/Package.h"

#include "Net/Session.h"
#include "Net/SessionManager.h"
#include "Net/Server.h"

#include "Net/IOCP/IOCPSession.h"
#include "Net/IOCP/IOCPServer.h"

#include "Contents/ContentsProcess.h"

#endif