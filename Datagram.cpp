#include "Datagram.h"
namespace Tool
{
	namespace Network
	{
		Datagram::Datagram(b8 data, u32 size)
		{
			unt i;
			for(i = 0; i < size; ++i)
				this->data.push(data[i]);
		}
		Datagram::Datagram(void){}
		Datagram::~Datagram(void)
		{
		}
		b8 Datagram::Data(b8 data, u32 size)
		{
			unt dsize = Size();
			unt i;
			for(i = 0; i < dsize && i < size; ++i)
			{
				data[i] = this->data.front();
				this->data.pop();
			}
			return data;
		}
		b8 Datagram::Data(void)
		{
			unt size = Size();
			b8 data = new w8[size];

			unt i;
			for(i = 0; i < size; ++i)
			{
				data[i] = this->data.front();
				this->data.pop();
			}
			return data;
		}

		//template<typename t> void Datagram::Write(t & value) ===> Datagram.inl
		//template<typename t> t Datagram::Read(void) ===> Datagram.inl

		void Datagram::Writeb8(b8 value, u32 size)
		{
			unt i;
			for(i = 0; i < size; ++i)
				data.push(value[i]);
		}
		u32  Datagram::Readb8 (b8 value, u32 size)
		{
			unt dsize = data.size();
			u32 i;
			for(i = 0; i < size && dsize; ++i)
			{
				value[i] = data.front();
				data.pop();
			}
			return i + 1;
		}

		u32  Datagram::Size(void) const
		{
			return data.size();
		}
	}
}
