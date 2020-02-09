#include "WSA.h"

namespace Tool
{
	namespace Network
	{
		WSA::WSA(void)
		{
			WSAStartup(MAKEWORD(2,2), &data);
		}
		WSA::~WSA()
		{
			WSACleanup();
		}
		char* WSA::GetDescription(void)
		{
			return (char*)(data.szDescription);
		}
		char* WSA::GetSystemStatus(void)
		{
			return (char*)(data.szSystemStatus);
		}
		uint16_t WSA::GetVersion(void)
		{
			return data.wVersion;
		}
		uint16_t WSA::GetHighestSupportedVersion(void)
		{
			return data.wHighVersion;
		}
	}
}