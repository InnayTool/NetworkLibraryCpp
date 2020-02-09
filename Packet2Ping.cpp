#include "Packet2Ping.h"
#include "Datagram.h"

namespace Tool
{
	namespace Network
	{
		Packet2Ping::Packet2Ping(void)
		{
			SYSTEMTIME time;
			this->shallRespond = true;
			this->iD = 2;
			GetSystemTime(&time);
			this->startTime = time.wMilliseconds + 1000 * time.wSecond + time.wMinute * 60000;
		}
		Packet2Ping::Packet2Ping(bool shallRespond)
		{
			SYSTEMTIME time;
			this->shallRespond = shallRespond;
			this->iD = 2;
			GetSystemTime(&time);
			this->startTime = time.wMilliseconds + 1000 * time.wSecond + time.wMinute * 60000;
		}
		int Packet2Ping::Set(Datagram* data)
		{
			SYSTEMTIME time;
			this->shallRespond = data->Read<bool>();
			this->startTime = data->Read<u32>();
			GetSystemTime(&time);
			this->elapsedTime = (time.wMilliseconds + 1000 * time.wSecond + time.wMinute * 60000) - this->startTime;
			return 0;
		}
		Datagram* Packet2Ping::Get(Datagram* data)
		{
			data->Write(this->shallRespond);
			data->Write<i32>(this->startTime);
			return data;
		}
		u32 Packet2Ping::StartTime(void)
		{
			return this->startTime;
		}
		u32 Packet2Ping::ElapsedTime(void)
		{
			return this->elapsedTime;
		}
	}
}
