#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstddef>
#include <cstdint>

namespace my
{

	class string
	{
	public:
		string();
		string(const string& str);
		string(const char* s);
		string(size_t n, char c);

		string& operator= (const string& str);
		string& operator= (const char* s);
		string& operator= (char c);

	private:
		int8_t slen;
		union {
			struct ldata {
				size_t len, res;
				char *ptr;
			} l;
			char buf[40];
		} data;
	};

}

#endif//MY_STRING_HPP