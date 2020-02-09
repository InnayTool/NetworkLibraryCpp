#include "Network.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace Tool
{
	namespace Network
	{
		class UdpConnection
		{
		public:
			UdpConnection(std::string address, int16_t localPort);
			uint32_t Send(std::vector<int> data);
		};
	}

}