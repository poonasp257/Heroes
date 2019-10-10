#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <process.h>

#include <string>

#include "Include/rapidjson/document.h"

#include "Util/singleton.h"

#include "Net/server.h"
#include "Net/IOCPServer.h"