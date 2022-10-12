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
	if (size < my::string::BUFSIZE)
	{
		this->slen = size;
		memcpy(this->data.buf, str.c_str(), size + 1);
		return;
	}

	this->slen = -1;
	this->data.l.len = size;
	this->data.l.res = size + 1;
	this->data.l.ptr = new char[size + 1];
	memcpy(this->data.l.ptr, str.c_str(), size + 1);
}

my::string::string(const char* s)
{
	size_t size = strlen(s);
	if (size < my::string::BUFSIZE)
	{
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
	if (n < my::string::BUFSIZE)
	{
		this->slen = n;
		memset(this->data.buf, c, n);
		this->data.buf[n] = 0;
		return;
	}

	this->slen = -1;
	this->data.l.len = n;
	this->data.l.res = n+1;
	this->data.l.ptr = new char[n+1];

	memset(this->data.l.ptr, c, n);
	this->data.l.ptr[n] = 0;
}

my::string& my::string::operator= (const my::string& str)
{
	size_t size = str.size();
	if (size < my::string::BUFSIZE)
	{
		if (this->slen < 0)
			delete[] this->data.l.ptr;

		this->slen = size;
		memcpy(this->data.buf, str.c_str(), size + 1);
		return *this;
	}

	if (this->slen < 0 && size >= this->data.l.res)
	{
		delete[] this->data.l.ptr;
		this->slen = 0;
	}

	if (this->slen >= 0)
	{
		this->slen = -1;
		this->data.l.res = size + 1;
		this->data.l.ptr = new char[size + 1];
	}
	
	this->data.l.len = size;
	memcpy(this->data.l.ptr, str.c_str(), size + 1);
	return *this;
}

my::string& my::string::operator= (const char* s)
{
	size_t size = strlen(s);
	if (size < my::string::BUFSIZE)
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

	if (this->slen >= 0)
	{
		this->slen = -1;
		this->data.l.res = size + 1;
		this->data.l.ptr = new char[size + 1];
	}
	
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

my::string& my::string::operator+= (const my::string& str)
{
	size_t isize = this->size(), size = str.size(), rsize = isize + size;

	if (this->slen >= 0 && rsize < my::string::BUFSIZE)
	{
		memcpy(this->data.buf + isize, str.c_str(), size + 1);
		this->slen = rsize;
		return *this;
	}

	char *p;

	if (this->slen >= 0 || rsize >= this->data.l.res)
	{
		p = new char[rsize + 1];

		if (this->slen < 0) {
			memcpy(p, this->data.l.ptr, isize);
			delete[] this->data.l.ptr;
		} else {
			memcpy(p, this->data.buf, isize);
			this->slen = -1;
		}

		this->data.l.ptr = p;
	}

	memcpy(this->data.l.ptr + isize, str.c_str(), size + 1);
	this->data.l.len = rsize;
	this->data.l.res = rsize + 1;

	return *this;
}

my::string& my::string::operator+= (const char* s)
{
	size_t isize = this->size(), rsize = isize + strlen(s);

	if (this->slen >= 0 && rsize < my::string::BUFSIZE)
	{
		strcpy(this->data.buf + isize, s);
		this->slen = rsize;
		return *this;
	}

	char *p;

	if (this->slen >= 0 || rsize >= this->data.l.res)
	{
		p = new char[rsize + 1];

		if (this->slen < 0) {
			memcpy(p, this->data.l.ptr, isize);
			delete[] this->data.l.ptr;
		} else {
			memcpy(p, this->data.buf, isize);
			this->slen = -1;
		}

		this->data.l.ptr = p;
	}

	strcpy(this->data.l.ptr + isize, s);
	this->data.l.len = rsize;
	this->data.l.res = rsize + 1;

	return *this;
}

my::string& my::string::operator+= (char c)
{
	size_t isize = this->size();

	if (this->slen >= 0 && isize + 1 < my::string::BUFSIZE)
	{
		this->data.buf[this->slen] = c;
		this->data.buf[++this->slen] = 0;
		return *this;
	}

	char *p;

	if (this->slen >= 0 || isize + 1 >= this->data.l.res)
	{
		p = new char[isize + 2];

		if (this->slen < 0) {
			memcpy(p, this->data.l.ptr, isize);
			delete[] this->data.l.ptr;
		} else {
			memcpy(p, this->data.buf, isize);
			this->slen = -1;
		}

		this->data.l.ptr = p;
	}

	this->data.l.ptr[isize] = c;
	this->data.l.ptr[isize + 1] = 0;
	this->data.l.len = isize + 1;
	this->data.l.res = isize + 2;

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

std::ostream& operator<< (std::ostream& o, const my::string& str)
{
	for (const char &c : str)
		o << c;
	
	return o;
}