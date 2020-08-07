#ifndef SERVER_CORE_H
#define SERVER_CORE_H

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#pragma comment(lib, "Winmm.lib")

// C standard library
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>

// C++ standard library
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <cmath>
#include <limits>
#include <chrono>

#include <string>
#include <array>
#include <list>
#include <queue>
#include <map>
#include <unordered_map>

#include <memory>
#include <thread>
#include <mutex>

#include <algorithm>
#include <regex>
#include <functional>
#include <future>

// vcpkg Library
#include <curl/curl.h>

#include "Include/rapidjson/document.h"
#include "Include/rapidjson/filereadstream.h"
#include "Include/rapidjson/filewritestream.h"
#include "Include/rapidjson/prettywriter.h"

#include "Util/Type.h"
#include "Util/Util.h"
#include "Util/Clock.h"
#include "Util/HttpRequest.h"
#include "Util/Assert.h"
#include "Util/ConfigManager.h"
#include "Util/Component/GameObject.h"
#include "Util/Component/Transform.h"

#include "Util/Boundary/BoundingObject2D.h"
#include "Util/Boundary/BoundingBox2D.h"
#include "Util/Boundary/BoundingCircle2D.h"
#include "Util/Boundary/BoundingObject.h"
#include "Util/Boundary/BoundingBox.h"
#include "Util/Boundary/BoundingCircle.h"

#include "Util/Lock/Lock.h"
#include "Util/Lock/LockManager.h"
#include "Util/Lock/ScopedLock.h"

#include "Util/Thread/Thread.h"
#include "Util/Thread/ThreadManager.h"

#include "Util/Logger/FileLogger.h"
#include "Util/Logger/ConsoleLogger.h"
#include "Util/Logger/SystemLogger.h"

#include "Util/Obfuscation/Obfuscation.h"
#include "Util/Obfuscation/XorObfuscation.h"

#include "Util/FSM/State.h"
#include "Util/FSM/StateMachine.h"

#include "Util/Task/Task.h"
#include "Util/Task/AsyncTaskManager.h"

#include "Util/Container/QuadTree.h"
#include "Util/Container/SynchronizedQueue.h"

#include "Net/Packet/Stream.h"
#include "Net/Packet/PacketType.h"
#include "Net/Packet/Packet.h"
#include "Net/Packet/NotifyPacket.h"
#include "Net/Packet/PacketAnalyzer.h"
#include "Net/Packet/PacketFactory.h"
#include "Net/Packet/Package.h"
#include "Net/Packet/PacketObfuscator.h"

#include "Net/Session.h"
#include "Net/SessionManager.h"
#include "Net/Server.h"

#include "Net/IOCP/IOCPSession.h"
#include "Net/IOCP/IOCPServer.h"

#include "Net/Terminal/TerminalSession.h"
#include "Net/Terminal/Terminal.h"
#include "Net/Terminal/TerminalManager.h"

#include "Contents/ContentsProcess.h"

#include "Database/ODBCDatabase.h"
#include "Database/Query.h"
#include "Database/DBManager.h"

#endif