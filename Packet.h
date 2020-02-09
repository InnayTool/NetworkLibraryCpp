#include "INCLUDE.H"
#pragma once
class Tool::Network::Packet
{
public:
	Packet() ;
	~Packet(void);
	u16 GetID(void);
	virtual int Set(Datagram* data) = 0;
	virtual Datagram* Get(Datagram* data) = 0;
protected:
	u16 iD;
};

