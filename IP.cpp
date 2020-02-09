#include "IP.h"

namespace Tool
{
	namespace Network
	{

		IP::IP(uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4)
		{
			memset(this->ipv6, 0, 12);
			this->ipv4 = (uint8_t*) &(this->ipv6[6]);
			this->ipv4[0] = _1;
			this->ipv4[1] = _2;
			this->ipv4[2] = _3;
			this->ipv4[3] = _4;
		}
		IP::IP(uint8_t ip[4])
		{
			memset(this->ipv6, 0, 12);
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			this->ipv4[0] = ip[0];
			this->ipv4[1] = ip[1];
			this->ipv4[2] = ip[2];
			this->ipv4[3] = ip[3];
		}
		IP::IP(uint16_t _1, uint16_t _2, uint16_t _3, uint16_t _4, uint16_t _5, uint16_t _6, uint16_t _7, uint16_t _8)
		{
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			this->ipv6[0] = _1;
			this->ipv6[1] = _2;
			this->ipv6[2] = _3;
			this->ipv6[3] = _4;
			this->ipv6[4] = _5;
			this->ipv6[5] = _6;
			this->ipv6[6] = _7;
			this->ipv6[7] = _8;
		}
		IP::IP(uint16_t ip[8])
		{
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			this->ipv6[0] = ip[0];
			this->ipv6[1] = ip[1];
			this->ipv6[2] = ip[2];
			this->ipv6[3] = ip[3];
			this->ipv6[4] = ip[4];
			this->ipv6[5] = ip[5];
			this->ipv6[6] = ip[6];
			this->ipv6[7] = ip[7];
		}
		IP::IP(std::string ip)
		{
			IN6_ADDR in6;
			IN_ADDR in;
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			if (inet_pton(AF_INET, ip.c_str(), &in) == 1)
			{
				memset(this->ipv6, 0, 12);
				*(IN_ADDR*)this->ipv4 = in;
				return;
			}
			if (inet_pton(AF_INET6, ip.c_str(), &in6) != 1)
				throw std::invalid_argument("The given string is no ip!");
		}
		IP::IP(IN_ADDR ip)
		{
			memset(this->ipv6, 0, 12);
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			*(IN_ADDR*)this->ipv4 = ip;
		}
		IP::IP(IN6_ADDR ip)
		{
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			*(IN6_ADDR*)this->ipv6 = ip;
		}
		IP::IP(uint32_t ip)
		{
			memset(this->ipv6, 0, 12);
			this->ipv4 = (uint8_t*)&(this->ipv6[6]);
			*(uint32_t*)this->ipv4 = ip;
		}
		bool IP::IsIPv4() const
		{
			for (int i = 0; i < 6; ++i)
				if (this->ipv6[i])
					return false;
			return true;
		}

		uint8_t  * IP::IPv4Data()
		{
			return this->ipv4;
		}

		uint16_t * IP::IPv6Data()
		{
			return this->ipv6;
		}

		std::string IP::toIPv4string() const
		{
			char str[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, (IN_ADDR*)this->ipv4, str, INET_ADDRSTRLEN);
			return std::string(str);
		}
		std::string IP::toIPv6string() const
		{
			char str[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, (IN6_ADDR*)this->ipv6, str, INET6_ADDRSTRLEN);
			return std::string(str);
		}

		uint16_t & IP::operator[](uint8_t i)
		{
			if (i > 7)
				throw std::out_of_range("No block above 7 in ip!");
			return this->ipv6[i];
		}

		uint16_t & IP::IPv6seg(uint8_t i)
		{
			if (i > 7)
				throw std::out_of_range("No block above 7 in ip!");
			return this->ipv6[i];
		}
		uint8_t  & IP::IPv4seg(uint8_t i)
		{
			if (i > 3)
				throw std::out_of_range("No block above 3 in ipv4!");
			return this->ipv4[i];
		}

		IN_ADDR & IP::In_Addr()
		{
			return *(IN_ADDR*)this->ipv4;
		}

		IN6_ADDR & IP::In6_Addr()
		{
			return *(IN6_ADDR*)this->ipv6;
		}
	}
}