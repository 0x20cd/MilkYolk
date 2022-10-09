#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <cstddef>

class mystring
{
public:
	mystring();
	mystring(const mystring& str);
	mystring(const char* s);
	mystring(size_t n, char c);

	mystring& operator= (const mystring& str);
	mystring& operator= (const char* s);
	mystring& operator= (char c);

private:
};

#endif//MYSTRING_HPP