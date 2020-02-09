#include "INCLUDE.H"

class Tool::Network::Address4
{
public:
	Address4(sockaddr_in  &	address);
	Address4(std::string  *	address);
	Address4(std::wstring *	address);
	Address4(const char*	address);
	Address4(const wchar_t*	address);
	Address4(IP4			address);

	Address4(std::string  *	iP, uint16_t port);
	Address4(std::wstring *	iP, uint16_t port);
	Address4(s8				iP, uint16_t port);
	Address4(s16			iP, uint16_t port);
	Address4(IP4			iP, uint16_t port);

	sockaddr_in		Tosockaddr			(void) const;
	std::string	 *	Tostring			(void) const;
	std::wstring *	Towstring			(void) const;
	const char	 *	Tos8				(void) const;
	const wchar_t*	Tos16				(void) const;

	std::string	 *	GetstringIP			(void) const;
	std::wstring *	GetwstringIP		(void) const;
	const char	 *	Gets8IP				(void) const;
	const wchar_t*	Gets16IP			(void) const;
	IP4				GetIP				(void) const;

	uint16_t		GetPort				(void) const;

	uint32_t		GetstringAddress	(std::string* address) const;
	uint32_t		GetwstringAddress	(std::wstring* address) const;
	uint32_t		Gets8Address		(s8 address) const;
	uint32_t		Gets16Address		(s16 address) const;

	uint32_t		GetstringIP			(std::string* iP) const;
	uint32_t		GetwstringIP		(std::wstring* iP) const;
	uint32_t		Gets8IP				(s8 iP) const;
	uint32_t		Gets16IP			(s16 iP) const;

private:
	inline sockaddr_in getAddressFromString(s8 address);
	inline sockaddr_in getAddressFromString(s16 address);

	sockaddr_in address;
};
