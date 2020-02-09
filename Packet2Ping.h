#include "INCLUDE.H"
#include "Packet.h"
class Tool::Network::Packet2Ping : public Tool::Network::Packet
{
public:
	Packet2Ping(void);
	Packet2Ping(bool shallResponse);
	int Set(Datagram* data);
	Datagram* Get(Datagram* data);
	u32 StartTime(void);
	u32 ElapsedTime(void);
private:
	bool shallRespond;
	i32 elapsedTime;
	i32 startTime;
};

