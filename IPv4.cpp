#include "IPv4.hpp"



namespace Tool {
	namespace Network {
		IPv4::IPv4(uint8_t _1, uint8_t _2, uint8_t _3, uint8_t _4)
		{
			buffer = (_4 << 24) + (_3 << 16) + (_2 << 8) + _1;
		}
		IPv4::IPv4(std::array<uint8_t, 4> ip)
		{
			buffer = (ip[3] << 24) + (ip[2] << 16) + (ip[1] << 8) + ip[0];
		}
		IPv4::IPv4(uint32_t ip)
		{
			buffer = ip;
		}
		IPv4::IPv4(std::string ip)
		{
			inet_pton(AF_INET, ip.c_str(), data());
		}
		IPv4::IPv4(IN_ADDR ip)
		{
			*((IN_ADDR*) data()) = ip;
		}

		std::string IPv4::tostring() const
		{
			char str[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, (void*)this->buffer, str, INET_ADDRSTRLEN);
			return std::string(str);
		}

		uint8_t * IPv4::data()
		{
			return (uint8_t*)&(this->buffer);
		}
		IN_ADDR IPv4::possixaddress()
		{
			return *((IN_ADDR*)data());
		}
		std::array<uint8_t, 4> IPv4::array()
		{
			std::array<uint8_t, 4> result;
			uint8_t* ip = data();
			result[0] = ip[3];
			result[1] = ip[2];
			result[2] = ip[1];
			result[3] = ip[0];
			return result;
		}
		uint8_t IPv4::operator[](uint8_t n)
		{
			return data()[3 - n];
		}
		uint8_t IPv4::at(uint8_t n)
		{
			if (n > 3)
				throw std::out_of_range("IPv4 has only 4 segments!");
			return data()[3 - n];
		}
		const IPv4 IPv4::any()
		{
			return IPv4(in4addr_any);
		}
	}
}