#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <cstddef>
#include <initializer_list>

namespace my
{

	template <class T>
	class list
	{
	private:
		size_t len;
		struct node
		{
			node *prev, *next;
			T value;
		} *firstNode, *lastNode;

	public:
		explicit list();
		explicit list(size_t n, const T& val = T());
		list(const list& x);
		list(list&& x);
		list(std::initializer_list<T> il);

		list& operator=(const list& x);

		class iterator;
		typedef const iterator const_iterator;

		class iterator
		{
		public:
			iterator(node* ptr = nullptr);
			iterator(const_iterator& it);

			iterator& operator=(const_iterator& it);

			T& operator*();
			const T& operator*() const;
			T* operator->();
			const T* operator->() const;

			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);

			bool operator==(const_iterator& itr) const;
			bool operator!=(const_iterator& itr) const;

		private:
			node *ptr;
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
	my::list<T>::node *last = nullptr, **nextp = &this->firstNode;

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
	my::list<T>::node *last = nullptr, **nextp = &this->firstNode;

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
my::list<T>::list(my::list<T>&& x)
{
	this->len = x.len;
	this->firstNode = x.firstNode;
	this->lastNode = x.lastNode;

	x.len = 0;
	x.firstNode = x.lastNode = nullptr;
}


template<class T>
my::list<T>::list(std::initializer_list<T> il) :
	len(il.size()),
	firstNode(nullptr),
	lastNode(nullptr)
{
	my::list<T>::node *last = nullptr, **nextp = &this->firstNode;

	for (const T& v : il)
	{
		*nextp = new my::list<T>::node{nullptr, nullptr, {v}};
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}

	this->lastNode = last;
}


template<class T>
my::list<T>& my::list<T>::operator=(const my::list<T>& x)
{
	this->clear();

	auto *last = nullptr, **nextp = &this->firstNode;

	for (const T& v : x)
	{
		*nextp = new my::list<T>::node{nullptr, nullptr, {v}};
		(*nextp)->prev = last;
		last = *nextp;
		nextp = &(*nextp)->next;
	}

	this->len = x.size();
	this->lastNode = last;

	return *this;
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


template<class T>
void my::list<T>::push_back(const T& val)
{
	auto **nextp = this->len++ ? &this->lastNode->next : &this->firstNode;

	this->lastNode = *nextp = new my::list<T>::node{this->lastNode, nullptr, {val}};
}

template<class T>
void my::list<T>::pop_back()
{
	if (!this->lastNode) // len = 0
		return;

	auto *t = this->lastNode;
	this->lastNode = t->prev;
	delete t;

	if (!this->lastNode) // len = 1
		this->firstNode = nullptr;

	--this->len;
}


template<class T>
void my::list<T>::clear()
{
	for(my::list<T>::node *p = this->lastNode, *t; p;)
	{
		t = p;
		p = p->prev;
		delete t;
	}

	this->len = 0;
	this->firstNode = this->lastNode = nullptr;
}


template<class T>
my::list<T>::~list()
{
	this->clear();
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
bool my::list<T>::iterator::operator==(typename my::list<T>::const_iterator& itr) const
{
	return this->ptr == itr.ptr;
}


template<class T>
bool my::list<T>::iterator::operator!=(typename my::list<T>::const_iterator& itr) const
{
	return this->ptr != itr.ptr;
}


#endif//MY_LIST_HPP