
namespace Tool
{
	namespace Network
	{
		template<typename t>	t	Datagram::Read(void)
		{
			t result;
			unt i;
			if(data.size() >= sizeof(t))
			{
				for (i = 0; i < sizeof(t); ++i)
				{
					 ((w8*)&result)[i] = this->data.front();
					 this->data.pop();
				}
				return result;
			}
			else
				throw std::out_of_range("Datagram hasn't");
		}
	    template<typename t> void Datagram::Write(t & value)
		{
			unt i;
			for(i = 0; i < sizeof(value); ++i)
				data.push(((w8*)&value)[i]);
		}
		template<bool> bool	Datagram::Read(void)
		{
			bool result;
			if(data.size() >= 1)
			{
				result = (this->data.front()?true:false);
				this->data.pop();
				return result;
			}
			else
				throw std::out_of_range("Datagram hasn't any data!");
		}
		template<bool> void	Datagram::Write(bool & value)
		{
			data.push(value ? 1 : 0);
		}
	}
}
