#include "INCLUDE.H"
class Tool::Network::IP4
{
public:
	IP4(std::string* iP);
	IP4(std::wstring* iP);
	IP4(s8 iP);
	IP4(s16 iP);
	IP4(w32 iP);
	
	std::string* Tostring(void) const;
	std::wstring* Towstring(void) const;

	u32 Tostring(std::string* iP) const;
	u32 Towstring(std::wstring* iP) const;
	s8 Tos8(void) const;
	s16 Tos16(void) const;
	u32 Tos8(s8 address) const;
	u32 Tos16(s16 address) const;

	u32 Tow32(void) const;
private:
	u32 address;
};
