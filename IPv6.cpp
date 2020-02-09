#include "IPv6.hpp"



namespace Tool {
	namespace Network{
		IPv6::IPv6(uint16_t _1, uint16_t _2, uint16_t _3, uint16_t _4, uint16_t _5, uint16_t _6, uint16_t _7, uint16_t _8)
		{
			buffer[7] = _1;
			buffer[6] = _2;
			buffer[5] = _3;
			buffer[4] = _4;
			buffer[3] = _5;
			buffer[2] = _6;
			buffer[1] = _7;
			buffer[0] = _8;
		}
		IPv6::IPv6(std::array<uint16_t, 8> ip)
		{
			buffer[7] = ip[0];
			buffer[6] = ip[1];
			buffer[5] = ip[2];
			buffer[4] = ip[3];
			buffer[3] = ip[4];
			buffer[2] = ip[5];
			buffer[1] = ip[6];
			buffer[0] = ip[7];
		}

		IPv6::IPv6(std::string ip)
		{
			inet_pton(AF_INET6, ip.c_str(), data());
		}
		IPv6::IPv6(IN6_ADDR ip)
		{
			size_t i;
			for (i = 0; i < 8; ++i)
				buffer[i] = ip.u.Word[i];
		}

		std::string IPv6::tostring() const
		{
			char str[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, (void*)this->buffer, str, INET6_ADDRSTRLEN);
			return std::string(str);
		}

		uint16_t * IPv6::data()
		{
			return this->buffer;
		}
		IN6_ADDR IPv6::possixaddress()
		{
			IN6_ADDR result;
			size_t i;
			for (i = 0; i < 8; ++i)
				result.u.Word[i] = buffer[i];
			return result;
		}
		std::array<uint16_t, 8> IPv6::array()
		{	
			std::array<uint16_t, 8> result;
			size_t i;
			for (i = 0; i < 8; ++i)
				result[i] = buffer[i];
			return result;
		}
		uint16_t IPv6::operator[](uint8_t n)
		{
			return buffer[7 - n];
		}
		uint16_t IPv6::at(uint8_t n)
		{
			if (n > 7)
				throw std::out_of_range("No index bigger than 7");
			return buffer[7 - n];
		}
		const IPv6 IPv6::any()
		{
			return IPv6(in6addr_any);
		}

	}
}
