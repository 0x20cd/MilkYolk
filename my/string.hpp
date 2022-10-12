#ifndef MY_STRING_HPP
#define MY_STRING_HPP

#include <cstddef>
#include <cstdint>
#include <iostream>

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
		string& operator+= (const string& str);
		string& operator+= (const char* s);
		string& operator+= (char c);

		char& operator[] (size_t pos);
		const char& operator[] (size_t pos) const;
		const char* c_str() const;

		char* begin();
		char* end();
		const char* begin() const;
		const char* end() const;
		const char* cbegin() const;
		const char* cend() const;

		bool empty() const;
		size_t size() const;

		~string();

	private:
		static constexpr size_t BUFSIZE = 42;
		
		int8_t slen; // when slen >= 0, it contains length of the short string, stored in data.buf;
		             // when slen < 0, info about the string is stored in data.l
		union {
			struct {
				char *ptr; // ptr - storage for the long string
				size_t len, res; // len - size of the long string, stored in data.l.ptr;
				                 // res - number of bytes reserved in data.l.ptr;
			} l;
			char buf[BUFSIZE];
		} data;
	};

}

std::ostream& operator<< (std::ostream& o, const my::string& str);

#endif//MY_STRING_HPP