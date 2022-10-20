#ifndef MY_LIST_HPP
#define MY_LIST_HPP
#include <cstddef>

namespace my
{

	template <class T>
	class list
	{
	private:
		struct node
		{
			node *prev, *next;
			T value;
		} *firstNode, *lastNode;

	public:
		explicit list();
		explicit list(size_t n, const T& val = T());
		list(const list& x);

		class iterator;
		typedef const iterator const_iterator;

		class iterator
		{
		public:
			iterator(node* ptr = nullptr); // has to set ptr to NULL
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

		private:
			node *ptr;
		};

		iterator begin();
		iterator end();
		const_iterator begin() const;
		const_iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;

		bool empty();
		size_t size();

		~list();
	};

}

template<class T>
bool operator==(typename my::list<T>::const_iterator& itl,
                typename my::list<T>::const_iterator& itr);

template<class T>
bool operator!=(typename my::list<T>::const_iterator& itl,
                typename my::list<T>::const_iterator& itr);

#endif//MY_LIST_HPP