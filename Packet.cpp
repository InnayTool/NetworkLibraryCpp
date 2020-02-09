#include "Packet.h"
#include "Datagram.h"
namespace Tool
{
	namespace Network
	{
		Packet::Packet(void) {}
		Packet::~Packet(void) {}
		u16 Packet::GetID(void)
		{
			return this->iD;
		}
	}
}