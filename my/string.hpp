#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstddef>

namespace my
{

	class string
	{
	public:
		typedef size_t size_type;

		string();
		string(const string& str);
		string(const char* s);
		string(size_type n, char c);

		string& operator= (const string& str);
		string& operator= (const char* s);
		string& operator= (char c);

	private:
	};

}

#endif//MY_STRING_HPP