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

#include <algorithm>
#include <string>
#include <list>
#include <array>
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
#include "Net/Packet/Package.h"
#include "Net/Session.h"
#include "Net/IOCPSession.h"
#include "Net/SessionManager.h"
#include "Net/Server.h"
#include "Net/IOCPServer.h"