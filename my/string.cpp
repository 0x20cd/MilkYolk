#include "string.hpp"
#include <cstring>

my::string::string()
{
	this->slen = 0;
	this->data.buf[0] = 0;
}

my::string::string(const my::string& str)
{
	size_t size = str.size();
	if (size < sizeof(this->data.buf)/sizeof(char)) {
		this->slen = size;
		strcpy(this->data.buf, str.c_str());
		return;
	}

	this->slen = -1;
	this->data.l.len = size;
	this->data.l.res = size + 1;
	this->data.l.ptr = new char[size + 1];
	strcpy(this->data.l.ptr, str.c_str());
}

my::string::string(const char* s)
{
	size_t size = strlen(s);
	if (size < sizeof(this->data.buf)/sizeof(char)) {
		this->slen = size;
		strcpy(this->data.buf, s);
		return;
	}

	this->slen = -1;
	this->data.l.len = size;
	this->data.l.res = size + 1;
	this->data.l.ptr = new char[size + 1];
	strcpy(this->data.l.ptr, s);
}

my::string::string(size_t n, char c)
{
	if (n < sizeof(this->data.buf)/sizeof(char)) {
		this->slen = n;
		for (size_t i = 0; i < n; ++i)
			this->data.buf[i] = c;
		this->data.buf[n] = 0;
		return;
	}

	this->slen = -1;
	this->data.l.len = n;
	this->data.l.res = n+1;
	this->data.l.ptr = new char[n+1];
	for (size_t i = 0; i < n; ++i)
		this->data.l.ptr[i] = c;
	this->data.l.ptr[n] = 0;
}

my::string& my::string::operator= (const my::string& str)
{
	size_t size = str.size();
	if (size < sizeof(this->data.buf)/sizeof(char))
	{
		if (this->slen < 0)
			delete[] this->data.l.ptr;

		this->slen = size;
		strcpy(this->data.buf, str.c_str());
		return *this;
	}

	if (this->slen < 0 && size >= this->data.l.res)
	{
		delete[] this->data.l.ptr;
		this->slen = 0;
	}

	if (this->slen >= 0) {
		this->data.l.res = size + 1;
		this->data.l.ptr = new char[size + 1];
	}
	
	this->slen = -1;
	this->data.l.len = size;
	strcpy(this->data.l.ptr, str.c_str());
	return *this;
}

my::string& my::string::operator= (const char* s)
{
	size_t size = strlen(s);
	if (size < sizeof(this->data.buf)/sizeof(char))
	{
		if (this->slen < 0)
			delete[] this->data.l.ptr;

		this->slen = size;
		strcpy(this->data.buf, s);
		return *this;
	}

	if (this->slen < 0 && size >= this->data.l.res)
	{
		delete[] this->data.l.ptr;
		this->slen = 0;
	}

	if (this->slen >= 0) {
		this->data.l.res = size + 1;
		this->data.l.ptr = new char[size + 1];
	}
	
	this->slen = -1;
	this->data.l.len = size;
	strcpy(this->data.l.ptr, s);
	return *this;
}

my::string& my::string::operator= (char c)
{
	if (this->slen < 0)
		delete[] this->data.l.ptr;

	this->slen = 1;
	this->data.buf[0] = c;
	this->data.buf[1] = 0;
	return *this;
}

char& my::string::operator[] (size_t pos)
{
	if (this->slen < 0)
		return this->data.l.ptr[pos];

	return this->data.buf[pos];
}

const char& my::string::operator[] (size_t pos) const
{
	if (this->slen < 0)
		return this->data.l.ptr[pos];

	return this->data.buf[pos];
}

const char* my::string::c_str() const
{
	if (this->slen < 0)
		return this->data.l.ptr;
	
	return this->data.buf;
}

char* my::string::begin()
{
	if (this->slen < 0)
		return this->data.l.ptr;
	
	return this->data.buf;
}

char* my::string::end()
{
	if (this->slen < 0)
		return this->data.l.ptr + this->data.l.len;
	
	return this->data.buf + this->slen;
}

const char* my::string::begin() const
{
	if (this->slen < 0)
		return this->data.l.ptr;
	
	return this->data.buf;
}

const char* my::string::end() const
{
	if (this->slen < 0)
		return this->data.l.ptr + this->data.l.len;
	
	return this->data.buf + this->slen;
}

const char* my::string::cbegin() const
{
	if (this->slen < 0)
		return this->data.l.ptr;
	
	return this->data.buf;
}

const char* my::string::cend() const
{
	if (this->slen < 0)
		return this->data.l.ptr + this->data.l.len;
	
	return this->data.buf + this->slen;
}

bool my::string::empty() const
{
	if (this->slen < 0)
		return this->data.l.len == 0;

	return this->slen == 0;
}

size_t my::string::size() const
{
	if (this->slen >= 0)
		return this->slen;
	return this->data.l.len;
}

my::string::~string()
{
	if (this->slen < 0)
		delete[] this->data.l.ptr;
}