#include "IP.hpp"
#include <array>


namespace Tool {
	namespace Network {
		class IPv6 //: public IP
		{
		public:
			IPv6(uint16_t _1,
				 uint16_t _2,
				 uint16_t _3,
				 uint16_t _4,
				 uint16_t _5,
				 uint16_t _6,
				 uint16_t _7,
				 uint16_t _8);

			IPv6(std::array<uint16_t, 8> ip);
			IPv6(std::string ip);
			IPv6(IN6_ADDR ip);

			std::string tostring() const;

			uint16_t * data();
			uint16_t operator[](uint8_t n);
			uint16_t at(uint8_t n);

			IN6_ADDR possixaddress();
			std::array<uint16_t, 8> array();



			static const IPv6 any();
		private:
			uint16_t buffer[8];

		};
	}
}