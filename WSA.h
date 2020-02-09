#include "INCLUDE.H"

class Tool::Network::WSA
{
public:
	WSA(void);
	~WSA();
	uint16_t GetHighestSupportedVersion(void);
	uint16_t GetVersion(void);
	char* GetDescription(void);
	char* GetSystemStatus(void);
private:
	WSADATA data;
};