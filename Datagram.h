#include "INCLUDE.H"
#ifndef DATAGRAM_INCLUDE
#define DATAGRAM_INCLUDE
class Tool::Network::Datagram
{
public:
	Datagram(b8 data, u32 size);
	Datagram(void);
	~Datagram(void);
	b8 Data(b8 data, u32 size);
	b8 Data(void);
	void Reset(w8* data);


	void Writeb8	(b8 value, u32 size);
	u32 Readb8		(b8 value, u32 size);

	template<typename t> t Read(void);
	template<bool> bool	Read(void);
	template<typename t> void Write(t & value);
	template<bool> void Write(bool & value);

	void Writestring(std::string value);
	std::string* Readstring(void);

	u32 Size(void) const;
private:
	std::queue<w8, std::deque<w8>> data;
};

#include "Datagram.inl"
#endif DATAGRAM_INCLUDE