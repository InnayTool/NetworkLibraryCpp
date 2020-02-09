#pragma once

#include "types.h"


namespace Tool
{
	namespace Network
	{
		class WSA;
		class Packet;
		class Packet2Ping;
		class Datagram;
		class Client;
		class IP4;
		class IP6;
		class Address4;
		class Address6;
	}
	namespace IO
	{
		class Std;
	}
}


#include "stl.h"
#include <WinSock2.h>
#include <Ws2ipdef.h>
#include <Windows.h>

//#include <winsock.h>

#pragma comment(lib,"ws2_32.lib")
