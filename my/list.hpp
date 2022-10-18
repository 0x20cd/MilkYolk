#ifndef MY_LIST_HPP
#define MY_LIST_HPP

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
		};

	public:
		explicit list(size_t n, const T& val = T());
		list(const list& x);

		class iterator
		{
		public:
			iterator(); // has to set ptr to NULL
			iterator(const iterator& it);

			iterator& operator=(const iterator& it);

			T& operator*();
			T* operator->();
			const T& operator*() const;
			const T* operator->() const;

			iterator& operator++();
			iterator operator++(int);
			iterator& operator--();
			iterator operator--(int);

		private:
			node *ptr;
		};

		typedef const iterator const_iterator;

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
bool operator==(typename my::list<T>::const_iterator &itl,
                typename my::list<T>::const_iterator &itr);

template<class T>
bool operator!=(typename my::list<T>::const_iterator &itl,
                typename my::list<T>::const_iterator &itr);

#endif//MY_LIST_HPP