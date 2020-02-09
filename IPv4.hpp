#ifndef IPV4_HPP_INCLUDED
#define IPV4_HPP_INCLUDED

#include "IP.hpp"
#include <array>

namespace Tool {
	namespace Network
	{
		class IPv4 //: public IP
		{
		public:
			IPv4(uint8_t _1,
				uint8_t _2,
				uint8_t _3,
				uint8_t _4);
			IPv4(uint8_t ip[4]);
			IPv4(std::array<uint8_t, 4> ip);
			IPv4(uint32_t ip);
			IPv4(std::string ip);
			IPv4(IN_ADDR ip);

			std::string tostring() const;

			uint8_t * data();
			uint8_t operator[](uint8_t n);
			uint8_t at(uint8_t n);

			IN_ADDR possixaddress();
			std::array<uint8_t, 4> array();

			

			static const IPv4 any();
		private:
			uint32_t buffer;

		};
	}
}

#endif//IPV4_HPP_INCLUDED
