#ifndef IP_HPP_INCLUDED
#define IP_HPP_INCLUDED
#include "Network.hpp"
#include <cstdint>
#include <string>
namespace Tool
{
	namespace Network
	{
		class IP
		{
		public:
			virtual std::string tostring() = 0;

			//virtual uint8_t * data() = 0;
			//virtual uint8_t operator[](uint8_t i);
			//virtual uint8_t at(uint8_t n);

			//virtual IN_ADDR possixaddress();
			//static const IN_ADDR any();
		protected:
			bool isipv4;
		};
	}
}

#endif//IP_HPP_INCLUDED
