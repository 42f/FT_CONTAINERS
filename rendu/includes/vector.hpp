#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <string>
# include <iterator>
# include <limits>
# include <algorithm>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

namespace ft	{

	template< typename T, typename T_alloc>
	class vectorBase	{

		public:

			// --------------------------------------------------------originaly struc vct impl
			// vectorBaseImpl()
			// : _Tp_alloc_type(), _head(), _tail(), _tailStorage()
			// { }

			// vectorBaseImpl(_Tp_alloc_type const& __a)
			// : _Tp_alloc_type(__a), _head(), _tail(), _tailStorage()
			// { }

			// void _M_swap_data(_Vector_impl& __x) _GLIBCXX_NOEXCEPT
			// {
			// std::swap(_M_start, __x._M_start);
			// std::swap(_M_finish, __x._M_finish);
			// std::swap(_M_end_of_storage, __x._M_end_of_storage);
			// }
			//----------------------------------------------------------------------------------


			typedef typename T_alloc::template rebind<T>::other				allocator_type;
			typedef typename T_alloc::reference								reference;
			typedef typename T_alloc::const_reference						const_reference;
			typedef typename T_alloc::pointer								pointer;
			typedef typename T_alloc::const_pointer							const_pointer;

			vectorBase( void ) : head(NULL), tail(NULL), tailStorage(NULL), alloc(allocator_type()) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
			}

			vectorBase( allocator_type const & userAlloc ) : head(NULL), tail(NULL), tailStorage(NULL), alloc(userAlloc) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> defaut with alloc " << __func__ << std::endl;
			}

			vectorBase( size_t n ) : head(NULL), tail(NULL), tailStorage(NULL), alloc(allocator_type()) {

				initStorage(n + (n>>1));
				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
			}

			vectorBase( size_t n, allocator_type const & userAlloc ) : head(NULL), tail(NULL), tailStorage(NULL), alloc(userAlloc) {

				initStorage(n + (n>>1));
				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> fill with alloc " << __func__ << std::endl;
			}

			~vectorBase( void )	{

				deleteStorage(tailStorage - head);
				if (DEBUG_MODE >= 2) std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			// static void	putvectorBaseInfos(vectorBase<T> const &n) {
			// 	std::cout << "-- vectorBase: " << &n << std::endl;
			// 	std::cout << "head        -> " << n.head << " @ " << &(n.head) << std::endl;
			// 	std::cout << "tail        -> " << n.tail << " @ " << &(n.tail) << std::endl;
			// 	std::cout << "tailStorage -> " << n.tailStorage << " @ " << &(n.tailStorage) << std::endl;
			// }

			pointer			head;
			pointer			tail;
			pointer			tailStorage;
			allocator_type	alloc;


		protected:
			void
			initStorage( size_t n )	{
				if (n > 0)	{
					this->head = this->alloc.allocate(n);
					this->tail = this->head;
					this->tailStorage = this->head + n;
					if (DEBUG_MODE >= 2) {
						std::cout << __func__ << std::endl;
						for (size_t i = 0; head + i != tailStorage; ++i)	{
							std::cout << "[" << i << "] uninitialized ";
							std::cout << " @ " << head + i << std::endl;
						}
					}
				}
			}

		private:
			void
			deleteStorage( size_t n )	{
				this->alloc.deallocate(head, n);
				if (DEBUG_MODE >= 2) std::cout << __func__ << std::endl;
			}
		}; // ----------------- Class vectorBase





	template< typename T, class T_alloc = std::allocator<T> >
	class vectorIterator : public std::iterator< std::random_access_iterator_tag, T >
	{
		public:
			typedef vectorIterator<T, T_alloc>			iterator;
			// typedef	vectorBase::pointer<T, T_alloc>		pointer;
			typedef ptrdiff_t							distance;

			vectorIterator( void ) :_ptr(NULL) {}
			vectorIterator(T* src) :_ptr(src) {}
			vectorIterator(const iterator& itSrc) : _ptr(itSrc._ptr) {}

			iterator&	operator++( void ) {
				_ptr++;
				return *this;
			}

			iterator 	operator++( int ) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}

			iterator&	operator--( void ) {
				_ptr--;
				return *this;
			}

			iterator 	operator--( int ) {
				iterator tmp(*this);
				operator--();
				return tmp;
			}

			distance	operator- ( iterator rhs ) { return this->_ptr - rhs._ptr; }


	// 		iterator	operator- ( distance n ) {

	// 			iterator tmpIt = *this;

	// 			while ( n > 0 )	{
	// 				tmpIt--;
	// 				n--;
	// 			}
	// 			return tmpIt;
	// 		}

	// 		iterator	operator+ ( distance n ) {

	// 			iterator tmpIt = *this;

	// 			while ( n > 0 )	{
	// 				tmpIt++;
	// 				n--;
	// 			}
	// 			return tmpIt;
	// 		}

	// 		void	operator-= ( distance n ) {

	// 			*this = *this - n;
	// 		}

	// 		void	operator+= ( distance n ) {

	// 			*this = *this + n;
	// 		}

			bool 		operator==(const iterator& rhs) const { return _ptr==rhs._ptr; }
			bool 		operator!=(const iterator& rhs) const { return _ptr!=rhs._ptr; }
			// bool 		operator<(const iterator& rhs) const {

			// 	if (*this == rhs)
			// 		return false;
			// 	iterator	tmpIt = *this;
			// 	while (tmpIt._ptr != tmpIt._ptr->next && tmpIt != rhs)
			// 		tmpIt++;
			// 	return (tmpIt == rhs);
			// }

			T &	operator*() { return *_ptr; }

			T *		_ptr;

	}; //----------------- Class iterator


	template< typename T, typename T_alloc = std::allocator<T> >
	class vector : protected vectorBase<T, T_alloc> {


		public:
			typedef vectorBase<T, T_alloc>					vectorBase;
			typedef vectorIterator<T>						iterator;
			typedef std::reverse_iterator<iterator> 		reverse_iterator;
			// typedef const_iterator<T>						const_iterator;
			// typedef std::const_reverse_iterator<iterator>	const_reverse_iterator;
			typedef T										value_type;
			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef typename T_alloc::reference				reference;
			typedef typename T_alloc::const_reference		const_reference;
			typedef typename T_alloc::pointer				pointer;
			typedef typename T_alloc::const_pointer			const_pointer;

   			typedef typename vectorBase::allocator_type		allocator_type;

			/**
			 * @brief Default Constructor
			*/
			explicit vector( allocator_type const & userAlloc = allocator_type() ) : vectorBase(userAlloc) {

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> DEFAULT " << __func__ << std::endl;
			}

			/**
			 * @brief fill Constructor, allocate at least n memory blocks and
			 * construct n objects val.
			*/
			explicit vector( size_type n, value_type const & val = value_type(),
				allocator_type const & userAlloc = allocator_type() ) : vectorBase(n, userAlloc)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
				initFillVector(n, val);
			}


			/**
			 * @brief Range Constructor
			*/
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
				 allocator_type const & userAlloc = allocator_type() )
				 : vectorBase(userAlloc)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range pre dispatcher ! " << __func__ << std::endl;

				typename std::__is_integer<InputIterator>::__type	integer;
				vector_constructor_dispatch(first, last, userAlloc, integer);
			}

			/**
			 * @brief Copy Constructor
			*/
			explicit vector( vector const & src ) : vectorBase(src.size()) {

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;

				fillVector(src.begin(), src.end());
			}

			~vector( void )	{

				clearObject();
				if (DEBUG_MODE >= 1)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			size_type			max_size( void ) const	{ return this->alloc.max_size();  }
			bool				empty( void ) const		{ return (this->head == this->tail); }
			size_type			size( void ) const 		{ return (this->tail - this->head); }
			iterator			begin( void ) const		{ return (this->head); }
			iterator			end( void ) const 		{ return (this->tail); }
			reverse_iterator	rbegin( void ) const	{ return reverse_iterator(end()); }
			reverse_iterator	rend( void ) const 		{ return reverse_iterator(begin()); }
			reference			front( void ) 			{ return (*this->head); }
			reference			back( void ) 	 		{ return (*this->tail); }
			const_reference		front( void ) const		{ return (*this->head); }
			const_reference		back( void ) const 		{ return (*this->tail); }

			size_type			capacity( void ) const	{ return (this->tailStorage - this->head); }


			// vector&
			// operator= (const vector& x)	{

			// 	if (*this != x)
			// 		assign(x.begin(), x.end());
			// 	return *this;
			// }

		// 	void
		// 	pop_back( void )						{ erase(--end()); }
		// 	void
		// 	push_back (value_type const & val)		{ insert(end(), val); }
		// 	void
		// 	pop_front( void )						{ erase(begin()); }
		// 	void
		// 	push_front (value_type const & val)		{ insert(begin(), val); }

			// void
			// clear( void )	{ erase(begin(), end()); }


		// 	/**
		// 	 * @brief insert single element
		// 	*/
		// 	iterator insert(iterator position, const value_type& val)	{

		// 		node *	newNode = getNode(val);
		// 		if (_size < max_size())	{
		// 			if (_head == _tail || position == begin())
		// 				_head = newNode;
		// 			newNode->hook(position._ptr);
		// 			incSize();
		// 		}
		// 		return newNode;
		// 	}

		// 	/**
		// 	 * @brief insert n elements of val
		// 	*/
		// 	void insert (iterator position, size_type n, const value_type& val)	{

		// 		if (n + _size <= max_size())
		// 		{
		// 			for(; n > 0; --n)	{
		// 				insert(position, val);
		// 			}
		// 		}
		// 	}

		// 	/**
		// 	 * @brief insert range of elements
		// 	 * check here if arguments of type InputIterator are integer
		// 	 * or iterators and dispatch to the right overload.
		// 	 * Cf. /usr/include/c++/7/bits/cpp_type_traits.h line 136
		// 	 * for implementation. Basicly __is_integer is a template function
		// 	 * which, by default containts __false_type as __type, unless
		// 	 * it is one of the integer types so it contains __true_type
		// 	 * Here we create integet wich will be of type __true_type
		// 	 * or __false_type, and by calling inster_dispatch with it, the right
		// 	 * overload is called.
		// 	 * insert_dispatch taking __true_type will execute code for
		// 	*/
		// 	template <class InputIterator>
		// 	void
		// 	insert (iterator position, InputIterator first,
		// 	InputIterator last)	{

		// 		typename std::__is_integer<InputIterator>::__type	integer;
		// 		insert_dispatch(position, first, last, integer);
		// 	}

		// 	iterator
		// 	erase (iterator position)	{

		// 		node * cursor = position._ptr;
		// 		node * returnCursor = cursor->next;
		// 		if (_size > 0)	{
		// 			if (cursor == _head)
		// 				_head = _head->next;
		// 			cursor->unhook();
		// 			_alloc.destroy(cursor);
		// 			_alloc.deallocate(cursor, 1);
		// 			decSize();
		// 		}
		// 		return returnCursor;
		// 	}

		// 	iterator
		// 	erase (iterator first, iterator last)	{

		// 		iterator tmpCursor = first;
		// 		while (first != last)
		// 		{
		// 			tmpCursor = first;
		// 			first++;
		// 			erase(tmpCursor);
		// 		}
		// 		return last;
		// 	}


		// 	void
		// 	resize (size_type n, value_type val = value_type())	{

		// 		if (n < _size)	{
		// 			typename ft::vector<T>::iterator it = begin();
		// 			for(size_type i = 0; i < n; i++)
		// 				it++;
		// 			erase(it, end());
		// 		}
		// 		else if (n > _size)
		// 			insert(end(), n - _size, val);
		// 	}

		// 	void
		// 	swap (vector& src)	{

		// 		node *		_headTmp = src._head;
		// 		node *		_tailTmp = src._tail;
		// 		size_type	_sizeTmp = src._size;

		// 		src._head = _head;
		// 		src._tail = _tail;
		// 		src._size = _size;

		// 		_head = _headTmp;
		// 		_tail = _tailTmp;
		// 		_size = _sizeTmp;
		// 	}

			// /**
			//  * @brief Here we use the same technic as for insert : the type
			//  *  integer is  used to call the right overload.
			// */
			// template <class InputIterator>
			// void assign (InputIterator first, InputIterator last)	{

			// 	typename std::__is_integer<InputIterator>::__type	integer;
			// 	assign_dispatch(first, last, integer);
			// }

			// void assign(size_type n, const value_type& val)	{

			// 	clear();
			// 	insert(begin(), n, val);
			// }

		// /**
		//  *	@brief entire vector (1)
		// */
		// 	void
		// 	splice (iterator position, vector& x)	{

		// 		splice(position, x, x.begin(), x.end());
		// 	}

		// /**
		//  *	@brief single element (2)
		// */
		// 	void
		// 	splice (iterator position, vector& x, iterator it)	{

		// 		splice(position, x, it, ++it);
		// 	}	// splice

		// /**
		//  *	@brief element range (3)
		// */
		// 	void
		// 	splice (iterator position, vector& x, iterator first, iterator last)	{

		// 		if (x.size() > 0)	{

		// 			size_type sizeSplice = std::distance(first, last);

		// 			first._ptr->transfer(first._ptr, last._ptr);
		// 			first._ptr->hook(position._ptr);
		// 			if (position._ptr == _head)
		// 				_head = first._ptr;
		// 			if (first._ptr == x._head)
		// 				x._head = last._ptr;
		// 			this->incSize(sizeSplice);
		// 			x.decSize(sizeSplice);
		// 			if (x.size() == 0)
		// 				x._head = x._tail;
		// 		}
		// 	}	// splice


		// 	void remove (const value_type& val)	{

		// 		iterator	itFind = begin();

		// 		while ((itFind = std::find(itFind, end(), val)) != end())
		// 			itFind = erase(itFind);
		// 	}	// remove

		// 	template <class Predicate>
		// 	void
		// 	remove_if (Predicate pred)	{

		// 		iterator	itFind = begin();

		// 		while ((itFind = std::find_if(itFind, end(), pred)) != end())
		// 			itFind = erase(itFind);
		// 	}	// remove


		// 	void
		// 	unique( void )	{ unique(equality()); }

		// 	template <class BinaryPredicate>
		// 	void
		// 	unique (BinaryPredicate binary_pred)	{

		// 		iterator	itFind = begin();
		// 		iterator	itEndGroup = begin();

		// 		while ((itFind = std::adjacent_find(itEndGroup, end(), binary_pred)) != end())	{
		// 			itEndGroup = itFind;
		// 			while (binary_pred(*itFind, *itEndGroup) == true && itEndGroup != end())
		// 				itEndGroup++;
		// 		 	erase(++itFind, itEndGroup);
		// 		}

		// 	} // unique

		// 	void merge (vector& x)	{ merge(x, smaller_than()); }

		// 	template <class Compare>
		// 	void
		// 	merge (vector& x, Compare comp)	{

		// 		if (*this == x)
		// 			return ;
		// 		iterator	thisCursor = this->begin();
		// 		while (x.empty() == false)	{
		// 			while (thisCursor != this->end() && comp(*x.begin(), *thisCursor) == false)	{
		// 				thisCursor++;
		// 			}
		// 			this->splice(thisCursor, x, x.begin());
		// 		}
		// 		if (x.empty() == false)
		// 			this->splice(this->end(), x);
		// 	} // merge

		// 	void sort() { sort(smaller_than()); }

		// 	template <class Compare>
		// 	void
		// 	sort (Compare comp)	{

		// 		std::sort(begin(), end(), comp);
		// 	} // sort

		// 	void
		// 	reverse( void )	{


		// 		node * lastElem = _tail->prev;
		// 		node * newHead = lastElem;
		// 		node::swap(*_head, *lastElem);
		// 		_head = newHead;

		// 		size_t		swapSize = ((size() / 2) % 2 == 0) ?
		// 					((size() - 2) / 2) : ((size() - 2) / 2);

		// 		iterator	it = begin() + 1;
		// 		iterator	ite = end() - 2;
		// 		iterator	tmpIt = it;
		// 		iterator	tmpIte = ite;
		// 		for (size_t i = 0; i < swapSize ; i++)	{

		// 			tmpIt = it + 1;
		// 			tmpIte = ite - 1;
		// 			if (DEBUG_MODE >= 2)
		// 				std::cout << "SWAP: " <<  *it << " ; " << *ite << std::endl;
		// 			node::swap(*it._ptr, *ite._ptr);
		// 			it = tmpIt;
		// 			ite = tmpIte;
		// 		}

		// 	} // reverse

		// protected:
		// 	node *			_head;
		// 	node *			_tail;
		// 	size_type		_size;
		// 	allocator_type	_alloc;

		// private:

		// 	void	incSize( size_type n = 1 )	{ _size += n; }
		// 	void	decSize( size_type n = 1 )	{ _size -= n; }

		// 	struct smaller_than {
		// 		bool operator() (value_type const & a, value_type const & b) const
		// 		{ return (a<b); }
		// 	};

		// 	struct equality {
		// 		bool operator() (value_type const & a, value_type const & b) const
		// 		{ return (a==b); }
		// 	};


		// 	template <class InputIterator>
		// 	void
		// 	assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

		// 		clear();
		// 		insert(begin(), first, last);
		// 	}

		// 	template<typename integer>
		// 	void
		// 	assign_dispatch (integer n, integer val, std::__true_type)	{

		// 		assign(static_cast<size_type>(n), static_cast<value_type>(val));
		// 	}


			/**
			 * @brief Fill Constructor actual function
			*/
			template <class integer>
			void
			vector_constructor_dispatch (integer n, integer const & val,
				allocator_type const &, std::__true_type)	{

				if (DEBUG_MODE >= 1)	{
					std::cout << "dispatch --> __true_type " << __func__ << std::endl;
					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
				}
				this->initStorage(n);
				initFillVector(n, val);
			}

			/**
			 * @brief Range Constructor actual function
			*/
			template <class InputIterator>
			void
			vector_constructor_dispatch (InputIterator first, InputIterator last,
				 allocator_type const &, std::__false_type)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range : " << __func__ << std::endl;

				size_t	n = std::distance(first, last);
				this->initStorage(n * 2);
				fillVector(first, last);
			}


		// 	template<typename integer>
		// 	void
		// 	insert_dispatch(iterator position, integer n, integer val,
		// 	std::__true_type)	{
		// 		insert(position, static_cast<size_type>(n),
		// 			static_cast<value_type>(val));
		// 	}

		// 	template<typename InputIterator>
		// 	void
		// 	insert_dispatch(iterator position, InputIterator first,
		// 	InputIterator last, std::__false_type)	{
		// 		for (; first != last; ++first)	{
		// 			insert(position, *first);
		// 		}
		// 	}

			/**
			 * @brief Construct objects at alocated memory, to be used by
			 * constructors
			*/
			void
			fillVector(iterator first, iterator last)	{

				for (;first != last; first++)	{
					this->alloc.construct(this->tail, *first);
					this->tail++;
					if (this->tail == this->tailStorage)
						std::cout << "RESIZE HERE" << std::endl;
				}
			}

			/**
			 * @brief Construct objects at alocated memory, to be used by
			 * constructors
			*/
			void
			initFillVector(size_type n, value_type const & val)	{

				this->tail = this->head + n;
				for (; n > 0; --n){
					this->alloc.construct(this->tail - n, val);
				}
				if (DEBUG_MODE >= 3)	{
					std::cout << __func__ << std::endl;
					for (T* cursor = this->head; cursor != this->tail; ++cursor)
						std::cout << "val = " << *cursor << " @ " << cursor << std::endl;
					for (T* cursor = this->tail; cursor != this->tailStorage; ++cursor)
						std::cout << "after tail: val = " << cursor << std::endl;
				}
			}


			/**
			 * @brief Reserve
			*/
			void
			reserve (size_type n) {

				if (n > this->capacity())	{
					pointer		oldHead = this->head;
					size_type	oldSize = this->size();
					size_type	oldCapacity = this->capacity();

					reallocateBigger(n);

					destroyObjects(oldHead, oldSize);
					this->alloc.deallocate(oldHead, oldCapacity);
				}
			}

			void
			reallocateBigger(size_type n)	{

				if (n > this->capacity())	{

					iterator	oldHeadIt = begin();
					iterator	oldTailIt = end();

					this->initStorage(n);
					std::copy(oldHeadIt, oldTailIt, this->head);
					this->tail += oldTailIt - oldHeadIt;
				}
			}

			/**
			 * @brief Resize vector to new size n, reallocate if n > capacity
			*/
			void
			resize (size_type n, value_type val = value_type()) {

				if (n > this->size())
					resizeGrow(n, val);
				else if (n < this->size())
					resizeShrink(n);
			}

			void
			resizeShrink (size_type n) {

				size_type	newSize = size() - n;
				this->tail -= newSize;
				destroyObjects(this->tail, newSize);
			}

			void
			resizeGrow (size_type n, value_type val) {

				size_type	oldCapacity = this->capacity();
				size_type	oldSize = this->size();
				size_type	addedSize = n - oldSize;

				if (n > this->capacity())	{

					pointer		oldHead = this->head;

					reallocateBigger(n + (oldCapacity>>1));
					constructObjects(this->tail, addedSize, val);
					this->tail += addedSize;

					destroyObjects(oldHead, oldSize);
					this->alloc.deallocate(oldHead, oldCapacity);
				}
				else if (n > this->size())	{
					constructObjects(this->tail, addedSize, val);
					this->tail += addedSize;
				}
			}

			void
			constructObjects(pointer p, size_t n, value_type val = value_type())	{
				for (size_t i = 0; i < n; i++)	{
					this->alloc.construct(p + i, val);
				}
			}

			void
			destroyObjects(pointer p, size_t n)	{
				for (size_t i = 0; i < n; i++)	{
					this->alloc.destroy(p + i);
				}
			}


			void
			clearObject( void )	{

				if (DEBUG_MODE >= 3) std::cout << __func__ << std::endl;
				destroyObjects(this->head, this->size());
			}

		}; // ----------------- Class Vector

/*
	template <class T, class Alloc >
	void
	swap (list<T,Alloc>& x, list<T,Alloc>& y)	{

		x.swap(y);
	};

	template <class T, class Alloc>
	bool
	operator== (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{

		if (lhs.size() != rhs.size())
			return false;
		if (lhs.front() != rhs.front() || lhs.back() != rhs.back())
			return false;
		return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool
	operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{ return(!(lhs == rhs)); };


	template <class T, class Alloc>
	bool
	operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{

		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

	};

	template <class T, class Alloc>
	bool
	operator<= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{ return(!(lhs > rhs)); };

	template <class T, class Alloc>
	bool
	operator>  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{

		return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

	};

	template <class T, class Alloc>
	bool
	operator>= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs)	{ return(!(lhs < rhs)); };


*/
} // ----------------- ft namespace

#endif /* *****BVALETTE****** LIST_H */
