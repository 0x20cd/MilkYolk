#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <cstddef>
#include <cstdlib>
#include <initializer_list>

namespace my
{
	struct list_node_base
	{
		union { list_node_base *next, *first; };
		union { list_node_base *prev, *last; };
	};

	template <class T>
	class list
	{
	private:
		struct list_node : public list_node_base
		{
			list_node(const T& val = T()) : val(val) {}
			list_node(list_node_base *next, list_node_base *prev, const T& val) : list_node_base{next, prev}, val(val) {}
			T val;
		};

		list_node_base data;
		size_t len;

	public:
		explicit list();
		explicit list(size_t n, const T& val = T());
		list(const list& x);
		list(list&& x);
		list(std::initializer_list<T> il);

		list& operator=(const list& x);
		list& operator=(list&& x);
		list& operator=(std::initializer_list<T> il);

		class iterator;
		class const_iterator;

		class iterator
		{
		public:
			iterator(list_node_base* ptr = nullptr);
			iterator(const iterator& it);

			iterator& operator=(const iterator& it);

			T& operator*() const;
			T* operator->() const;

			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);

			friend bool operator==(const typename my::list<T>::iterator& it_l, const typename my::list<T>::iterator& it_r) {
				return it_l.ptr == it_r.ptr;
			}

			friend bool operator!=(const typename my::list<T>::iterator& it_l, const typename my::list<T>::iterator& it_r) {
				return it_l.ptr != it_r.ptr;
			}

		private:
			list_node_base *ptr;
		};

		class const_iterator
		{
		public:
			const_iterator(const list_node_base* ptr = nullptr);
			const_iterator(const iterator& it);
			const_iterator(const const_iterator& cit);

			const_iterator& operator=(const iterator& it);
			const_iterator& operator=(const const_iterator& cit);

			const T& operator*() const;
			const T* operator->() const;

			const_iterator& operator++();
			const_iterator operator++(int);
			const_iterator& operator--();
			const_iterator operator--(int);

			friend bool operator==(const typename my::list<T>::const_iterator& cit_l, const typename my::list<T>::const_iterator& cit_r) {
				return cit_l.ptr == cit_r.ptr;
			}

			friend bool operator!=(const typename my::list<T>::const_iterator& cit_l, const typename my::list<T>::const_iterator& cit_r) {
				return cit_l.ptr != cit_r.ptr;
			}

		private:
			const list_node_base *ptr;
		};

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		bool empty() const;
		size_t size() const;

		void push_back(const T& val);
		void pop_back();
		void clear();

		~list();
	};
}


////////////////////////////////////////////////////////////////////////////////////////////////////


template<class T>
my::list<T>::list()
 : data{&data, &data}
 , len(0)
{}


template<class T>
my::list<T>::list(size_t n, const T& val)
 : data{&data, &data}
 , len(n)
{
	my::list_node_base *last = &data, **nextp = &data.first;

	for (size_t i = 0; i < n; ++i)
	{
		*nextp = new list_node(val);
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}
	*nextp = &data;

	data.last = last;
}


template<class T>
my::list<T>::list(const my::list<T>& x)
 : data{&data, &data}
 , len(x.len)
{
	my::list_node_base *last = &data, **nextp = &data.first;

	for (const T& val : x)
	{
		*nextp = new list_node(val);
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}
	*nextp = &data;

	data.last = last;
}


template<class T>
my::list<T>::list(my::list<T>&& x)
 : data{x.data.first, x.data.last}
 , len(x.len)
{
	data.first->prev = data.last->next = &data;
	x.data.first = x.data.last = &x.data;
	x.len = 0;
}


template<class T>
my::list<T>::list(std::initializer_list<T> il)
 : data{&data, &data}
 , len(il.size())
{
	my::list_node_base *last = &data, **nextp = &data.first;

	for (const T& val : il)
	{
		*nextp = new list_node(val);
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}
	*nextp = &data;

	data.last = last;
}


template<class T>
my::list<T>& my::list<T>::operator=(const my::list<T>& x)
{
	if (this == &x)
		return *this;

	this->clear();
	new(this) list(x);

	return *this;
}


template<class T>
my::list<T>& my::list<T>::operator=(my::list<T>&& x)
{
	if (this == &x)
		return *this;

	this->clear();
	new(this) list(std::move(x));

	return *this;
}


template<class T>
my::list<T>& my::list<T>::operator=(std::initializer_list<T> il)
{
	this->clear();
	new(this) list(il);

	return *this;
}


template<class T>
typename my::list<T>::iterator my::list<T>::begin()
{
	return iterator(data.first);
}


template<class T>
typename my::list<T>::iterator my::list<T>::end()
{
	return iterator(&data);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::begin() const
{
	return const_iterator(data.first);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::end() const
{
	return const_iterator(&data);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::cbegin() const
{
	return const_iterator(data.first);
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::cend() const
{
	return const_iterator(&data);
}


template<class T>
bool my::list<T>::empty() const
{
	return !len;
}


template<class T>
size_t my::list<T>::size() const
{
	return len;
}


template<class T>
void my::list<T>::push_back(const T& val)
{
	my::list_node_base **nextp = len++ ? &data.last->next : &data.first;
	data.last = *nextp = new list_node(&data, data.last, val);
}

template<class T>
void my::list<T>::pop_back()
{
	if (len == 0)
		return;

	my::list_node_base *t = data.last;
	data.last = t->prev;
	data.last->next = &data;
	delete static_cast<list_node*>(t);

	if (--len == 0)
		data.first = &data;
}


template<class T>
void my::list<T>::clear()
{
	for(my::list_node_base *p = data.first, *t; p != &data; )
	{
		t = p;
		p = p->next;
		delete static_cast<list_node*>(t);
	}

	data.first = data.last = &data;
	len = 0;
}


template<class T>
my::list<T>::~list()
{
	for(my::list_node_base *p = data.first, *t; p != &data; )
	{
		t = p;
		p = p->next;
		delete static_cast<list_node*>(t);
	}
}


////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
///////////////////////                      ///////////////////////
///////////////////////    list::iterator    ///////////////////////
///////////////////////                      ///////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////


template<class T>
my::list<T>::iterator::iterator(list_node_base* ptr)
 : ptr(ptr)
{}


template<class T>
my::list<T>::iterator::iterator(const my::list<T>::iterator& it)
 : ptr(it.ptr)
{}


template<class T>
typename my::list<T>::iterator& my::list<T>::iterator::operator=(const my::list<T>::iterator& it)
{
	this->ptr = it.ptr;
}


template<class T>
T& my::list<T>::iterator::operator*() const
{
	return static_cast<my::list<T>::list_node*>(this->ptr)->val;
}


template<class T>
T* my::list<T>::iterator::operator->() const
{
	return &static_cast<my::list<T>::list_node*>(this->ptr)->val;
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
	my::list<T>::iterator it(this->ptr);
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
	my::list<T>::iterator it(this->ptr);
	this->ptr = this->ptr->prev;
	return it;
}


template<class T>
bool operator==(const typename my::list<T>::iterator& it_l, const typename my::list<T>::iterator& it_r)
{
	return it_l.ptr == it_r.ptr;
}


template<class T>
bool operator!=(const typename my::list<T>::iterator& it_l, const typename my::list<T>::iterator& it_r)
{
	return it_l.ptr != it_r.ptr;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////                            ///////////////////////
///////////////////////    list::const_iterator    ///////////////////////
///////////////////////                            ///////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


template<class T>
my::list<T>::const_iterator::const_iterator(const list_node_base* ptr)
 : ptr(ptr)
{}


template<class T>
my::list<T>::const_iterator::const_iterator(const typename my::list<T>::iterator& it)
 : ptr(it.ptr)
{}


template<class T>
my::list<T>::const_iterator::const_iterator(const typename my::list<T>::const_iterator& cit)
 : ptr(cit.ptr)
{}


template<class T>
typename my::list<T>::const_iterator& my::list<T>::const_iterator::operator=(const typename my::list<T>::iterator& it)
{
	this->ptr = it.ptr;
}


template<class T>
typename my::list<T>::const_iterator& my::list<T>::const_iterator::operator=(const typename my::list<T>::const_iterator& cit)
{
	this->ptr = cit.ptr;
}


template<class T>
const T& my::list<T>::const_iterator::operator*() const
{
	return static_cast<const my::list<T>::list_node*>(this->ptr)->val;
}


template<class T>
const T* my::list<T>::const_iterator::operator->() const
{
	return &static_cast<const my::list<T>::list_node*>(this->ptr)->val;
}


template<class T>
typename my::list<T>::const_iterator& my::list<T>::const_iterator::operator++()
{
	this->ptr = this->ptr->next;
	return *this;
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::const_iterator::operator++(int)
{
	my::list<T>::const_iterator cit(this->ptr);
	this->ptr = this->ptr->next;
	return cit;
}


template<class T>
typename my::list<T>::const_iterator& my::list<T>::const_iterator::operator--()
{
	this->ptr = this->ptr->prev;
	return *this;
}


template<class T>
typename my::list<T>::const_iterator my::list<T>::const_iterator::operator--(int)
{
	my::list<T>::const_iterator cit(this->ptr);
	this->ptr = this->ptr->prev;
	return cit;
}


template<class T>
bool operator==(const typename my::list<T>::const_iterator& cit_l, const typename my::list<T>::const_iterator& cit_r)
{
	return cit_l.ptr == cit_r.ptr;
}


template<class T>
bool operator!=(const typename my::list<T>::const_iterator& cit_l, const typename my::list<T>::const_iterator& cit_r)
{
	return cit_l.ptr != cit_r.ptr;
}


#endif//MY_LIST_HPP