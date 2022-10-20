#include "list.hpp"

template<class T>
my::list<T>::list() :
	len(0),
	firstNode(nullptr),
	lastNode(nullptr) {}


template<class T>
my::list<T>::list(size_t n, const T& val) :
	len(n),
	firstNode(nullptr),
	lastNode(nullptr)
{
	auto *last = nullptr, **nextp = &this->firstNode;

	for (size_t i = 0; i < n; ++i)
	{
		*nextp = new my::list<T>::node{nullptr, nullptr, {val}};
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}

	this->lastNode = last;
}


template<class T>
my::list<T>::list(const my::list<T>& x) :
	len(x.size()),
	firstNode(nullptr),
	lastNode(nullptr)
{
	auto *last = nullptr, **nextp = &this->firstNode;

	for (const T& v : x)
	{
		*nextp = new my::list<T>::node{nullptr, nullptr, {v}};
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}

	this->lastNode = last;
}


template<class T>
typename my::list<T>::iterator my::list<T>::begin()
{
	return my::list<T>::iterator(firstNode);
}


template<class T>
typename my::list<T>::iterator my::list<T>::end()
{
	return my::list<T>::iterator(nullptr);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::begin() const
{
	return my::list<T>::const_iterator(firstNode);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::end() const
{
	return my::list<T>::const_iterator(nullptr);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::cbegin() const
{
	return my::list<T>::const_iterator(firstNode);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::cend() const
{
	return my::list<T>::const_iterator(nullptr);
}


template<class T>
bool my::list<T>::empty() const
{
	return this->len==0;
}


template<class T>
size_t my::list<T>::size() const
{
	return this->len;
}


////////////////////////////////////////////////////////////////////
///////////////////////    list::iterator    ///////////////////////
////////////////////////////////////////////////////////////////////


template<class T>
my::list<T>::iterator::iterator(typename my::list<T>::node* ptr)
{
	this->ptr = ptr;
}


template<class T>
my::list<T>::iterator::iterator(typename my::list<T>::const_iterator& it)
{
	this->ptr = it.ptr;
}


template<class T>
typename my::list<T>::iterator& my::list<T>::iterator::operator=(typename my::list<T>::const_iterator& it)
{
	this->ptr = it.ptr;
	return *this;
}


template<class T>
T& my::list<T>::iterator::operator*()
{
	return this->ptr->value;
}


template<class T>
const T& my::list<T>::iterator::operator*() const
{
	return this->ptr->value;
}


template<class T>
T* my::list<T>::iterator::operator->()
{
	return &this->ptr->value;
}


template<class T>
const T* my::list<T>::iterator::operator->() const
{
	return &this->ptr->value;
}


template<class T>
typename my::list<T>::iterator& my::list<T>::iterator::operator++()
{
	this->ptr = this->ptr->next;
	return *this;
}


template<class T>
typename my::list<T>::iterator my::list<T>::iterator::operator++(int)
{
	typename my::list<T>::iterator it = *this;
	this->ptr = this->ptr->next;
	return it;
}


template<class T>
typename my::list<T>::iterator& my::list<T>::iterator::operator--()
{
	this->ptr = this->ptr->prev;
	return *this;
}


template<class T>
typename my::list<T>::iterator my::list<T>::iterator::operator--(int)
{
	typename my::list<T>::iterator it = *this;
	this->ptr = this->ptr->prev;
	return it;
}


template<class T>
bool operator==(typename my::list<T>::const_iterator& itl,
                typename my::list<T>::const_iterator& itr)
{
	return itl.ptr == itr.ptr;
}


template<class T>
bool operator!=(typename my::list<T>::const_iterator& itl,
                typename my::list<T>::const_iterator& itr)
{
	return itl.ptr != itr.ptr;
}
