#include "string.hpp"
#include <cstring>

my::string::string()
{
	this->slen = 0;
	this->data.buf[0] = 0;
}

my::string::string(const string& str)
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

my::string::~string()
{
	if (this->slen < 0)
		delete[] this->data.l.ptr;
}

size_t my::string::size() const
{
	if (this->slen >= 0)
		return this->slen;
	return this->data.l.len;
}

const char* my::string::c_str() const
{
	if (this->slen >= 0)
		return this->data.buf;
	return this->data.l.ptr;
}