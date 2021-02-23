#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include <memory>
# include <cstddef>
# include <string>
# include <iterator>
# include <limits>
# include <algorithm>
# include <stdexcept>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

namespace ft	{

	template< typename T, typename T_alloc>
	class vectorBase	{

		public:

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
			typedef const vectorIterator<T, T_alloc> 	const_iterator;
			typedef ptrdiff_t							distance;
			typedef typename T_alloc::reference			reference;
			typedef typename T_alloc::const_reference	const_reference;
			typedef typename T_alloc::pointer			pointer;
			typedef typename T_alloc::const_pointer		const_pointer;

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

			iterator	operator- ( distance n ) {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			const_iterator	operator- ( distance n ) const {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			iterator	operator+ ( distance n ) {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			const_iterator	operator+ ( distance n ) const {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			void			operator-= ( distance n )				{ *this = *this - n; }
			void			operator+= ( distance n )				{ *this = *this + n; }
			bool			operator==(const iterator& rhs) const	{ return _ptr==rhs._ptr; }
			bool			operator!=(const iterator& rhs) const	{ return _ptr!=rhs._ptr; }
			bool			operator<(const iterator& rhs) const	{ return _ptr< rhs._ptr; }
			reference		operator*()								{ return *_ptr; }
			const_reference	operator*()	const					{ return *_ptr; }

			pointer		_ptr;

	}; //----------------- Class iterator

	template< typename T, typename T_alloc = std::allocator<T> >
	class vector : protected vectorBase<T, T_alloc> {

		private:
			typedef vectorBase<T, T_alloc>					vectorBase;
		public:
			typedef T										value_type;
   			typedef typename vectorBase::allocator_type		allocator_type;
			typedef typename T_alloc::reference				reference;
			typedef typename T_alloc::const_reference		const_reference;
			typedef typename T_alloc::pointer				pointer;
			typedef typename T_alloc::const_pointer			const_pointer;
			typedef vectorIterator<T>						iterator;
			typedef const vectorIterator<T>					const_iterator;
			typedef std::reverse_iterator<iterator> 		reverse_iterator;
			typedef const reverse_iterator					const_reverse_iterator;
			typedef std::ptrdiff_t							difference_type;
			typedef size_t									size_type;

/******************************************************************************.
.******************************************************************************.
.*********** CONSTRUCTORS DESTRUCTOR ******************************************.
.******************************************************************************.
.******************************************************************************/


		public:
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

				if (size() > 0)
					clearObject();
				if (DEBUG_MODE >= 1)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

/******************************************************************************.
.******************************************************************************.
.*********** PUBLIC MEMBER FUNCTIONS ******************************************.
.******************************************************************************.
.******************************************************************************/

			size_type
			max_size( void ) const	{ return this->alloc.max_size();  }

			bool
			empty( void ) const		{ return (size() == 0); }

			size_type
			size( void ) const 		{ return (this->tail - this->head); }

			iterator
			begin( void ) 			{ return (this->head); }

			const_iterator
			begin( void ) const		{ return (this->head); }

			iterator
			end( void ) 	 		{ return (this->tail); }

			const_iterator
			end( void ) const 		{ return (this->tail); }

			reverse_iterator
			rbegin( void ) 			{ return reverse_iterator(end()); }

			const_reverse_iterator
			rbegin( void ) const	{ return reverse_iterator(end()); }

			reverse_iterator
			rend( void ) 	 		{ return reverse_iterator(begin()); }

			const_reverse_iterator
			rend( void ) const 		{ return reverse_iterator(begin()); }

			reference
			front( void ) 			{ return (*(this->head)); }

			const_reference
			front( void ) const		{ return (*(this->head)); }

			reference
			back( void ) 	 		{ return (*(this->tail - 1)); }

			const_reference
			back( void ) const 		{ return (*(this->tail - 1)); }

			size_type
			capacity( void ) const	{ return (this->tailStorage - this->head); }

			void
			pop_back( void )		{ if (size() > 0) erase(--end()); }

			void
			push_back (value_type const & val)	{ insert(end(), val); }

			void
			clear( void )			{ erase(begin(), end()); }

			vector&
			operator= (const vector& x)	{

				if (*this != x)
					assign(x.begin(), x.end());
				return *this;
			}

			/**
			 * @brief insert single element
			*/
			iterator insert(iterator position, const value_type& val)	{

				difference_type indexPos = position - begin();
				insert(position, 1, val);
				return begin() + indexPos; 		// to change
			}


			/**
			 * @brief insert n elements of val
			*/
			void insert (iterator position, size_type n, const value_type& val)	{

				if (capacity() == 0)	{
					this->initStorage(1);
					position = begin();
				}

				difference_type indexPos = position - begin();
				if (size() + n >= capacity())	{
					doReserve(capacity() + n + (capacity()>>1));
				}

				if (begin() + indexPos != end())	{
					if (size() > 1)	{
						memMoveRight(begin() + indexPos, end(), n);
					}
					destroyObjects(this->head + indexPos, size() - indexPos);
					this->tail += n;
					constructObjects(this->head + indexPos, n, val);
				}
				else {
					constructObjects(this->tail, n, val);
					this->tail += n;
				}
			}


			reference
			operator[] (size_type n)	{
				return (*(this->head + n));
			}

			const_reference
			operator[] (size_type n) const	{
				return (*(this->head + n));
			}


			reference
			at (size_type n)	{
				checkRange(n);
				return ((*this)[n]);
			}

			const_reference
			at (size_type n) const	{
				checkRange(n);
				return ((*this)[n]);
			}

			/**
			 * @brief insert range of elements
			 * check here if arguments of type InputIterator are integer
			 * or iterators and dispatch to the right overload.
			 * Cf. /usr/include/c++/7/bits/cpp_type_traits.h line 136
			 * for implementation. Basicly __is_integer is a template function
			 * which, by default containts __false_type as __type, unless
			 * it is one of the integer types so it contains __true_type
			 * Here we create integer wich will be of type __true_type
			 * or __false_type, and by calling insert_dispatch with it, the right
			 * overload is called.
			*/
			template <class InputIterator>
			void
			insert (iterator position, InputIterator first,
			InputIterator last)	{

				typename std::__is_integer<InputIterator>::__type	integer;
				insert_dispatch(position, first, last, integer);
			}

			iterator
			erase (iterator position)	{

				destroyObjects(position._ptr, 1);
				memMoveLeft(position + 1, end(), 1);
				this->tail -= 1;
				return position;
			}

			iterator
			erase (iterator first, iterator last)	{

				size_type			offset = first - begin();
				difference_type		len = last - first;
				destroyObjects(first._ptr, len);
				memMoveLeft(last, end(), len);
				this->tail -= len;
				return begin() + offset;
			}

			void
			resize (size_type n, value_type val = value_type())	{

				if (n < size())	{
					erase(end() - (size() - n), end());
				}
				else if (n > size())	{
					insert(end(), n - size(), val);
				}
			}

			void
			swap (vector& src)	{

				pointer 	headTmp = src.head;
				pointer 	tailTmp = src.tail;
				pointer		tailStorageTmp = src.tailStorage;

				src.head = this->head;
				src.tail = this->tail;
				src.tailStorage = this->tailStorage;

				this->head = headTmp;
				this->tail = tailTmp;
				this->tailStorage = tailStorageTmp;
			}

			/**
			 * @brief Here we use the same technic as for insert : the type
			 *  integer is  used to call the right overload.
			*/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)	{

				typename std::__is_integer<InputIterator>::__type	integer;
				assign_dispatch(first, last, integer);
			}

			void assign(size_type n, const value_type& val)	{

				clear();
				insert(begin(), n, val);
			}

			/**
			 * @brief Reserve: Requests that the vector capacity be at
			 * least enough to contain n elements.
			*/
			void
			reserve (size_type n) {

				if (n > max_size())	{
					throw std::length_error("ft::vector::reserve called with n > max_size");
				}
				else	{
					doReserve(n);
				}
			}

/******************************************************************************.
.******************************************************************************.
.*********** PRIVATE MEMBER FUNCTIONS AND HELPERS  ****************************.
.******************************************************************************.
.******************************************************************************/

		private:

			template <class InputIterator>
			void
			assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

				clear();
				insert(begin(), first, last);
			}

			template<typename integer>
			void
			assign_dispatch (integer n, integer val, std::__true_type)	{

				assign(static_cast<size_type>(n), static_cast<value_type>(val));
			}


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


			template<typename integer>
			void
			insert_dispatch(iterator position, integer n, integer val,
			std::__true_type)	{
				insert(position, static_cast<size_type>(n),
					static_cast<value_type>(val));
			}

			template<typename InputIterator>
			void
			insert_dispatch(iterator position, InputIterator first,
			InputIterator last, std::__false_type)	{

				if (capacity() == 0)	{
					this->initStorage(1);
					position = begin();
				}

				difference_type indexPos = position - begin();
				size_type		n = last - first;
				if (size() + n >= capacity())	{
					doReserve(capacity() + n + (capacity()>>1));
				}

				if (begin() + indexPos != end())	{
					if (size() > 1)	{
						memMoveRight(begin() + indexPos, end(), n);
					}
					destroyObjects(this->head + indexPos, size() - indexPos);
					this->tail += n;
					constructObjects(this->head + indexPos, first, last);
				}
				else {
					constructObjects(this->head + indexPos, first, last);
					this->tail += n;
				}
			}

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
						std::cout << "RESIZE HERE" << std::endl;			// not fixed yet
				}
			}

			/**
			 * @brief Construct objects at alocated memory, to be used by
			 * constructors
			*/
			void
			initFillVector(size_type n, value_type const & val)	{

				this->tail = this->head + n;
				for (size_t i = 0; i < n; i++){
					this->alloc.construct(this->head + i, val);
				}
			}



			/**
			 * @brief doReserve: No throw version of Reserve.
			*/
			void
			doReserve (size_type n) {

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
					constructObjects(this->head, oldHeadIt, oldTailIt);
					this->tail += oldTailIt - oldHeadIt;
				}
			}

			void
			constructObjects(pointer p, size_t n, value_type val = value_type())	{
				for (size_t i = 0; i < n; i++)	{
					this->alloc.construct(p + i, val);
				}
			}

			void
			constructObjects(pointer p, iterator first, iterator last)	{
				for (size_t i = 0; first != last; i++, first++)	{
					this->alloc.construct(p + i, *first);
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

			/**
			 * @brief Move [first, last] range by n memory blocks to theLeft
			*/
			void
			memMoveLeft(iterator first, iterator last, size_t n)	{			// to be tested
				while (first != last)	{
					constructObjects(first._ptr - n, 1, *first);
					destroyObjects(first._ptr, 1);
					first++;
				}
			}


			/**
			 * @brief Move [first, last] range by n memory blocks to the right
			*/
			void
			memMoveRight(iterator first, iterator last, size_t n)	{
				while (last != first)	{
					last--;
					constructObjects(last._ptr + n, 1, *last);
					destroyObjects(last._ptr, 1);
				}
			}

			void
			checkRange(size_type n)	const {
				if (n > size())	{
					throw std::out_of_range("Out of vector's range");
				}
			}
		}; // ----------------- Class Vector

	template <class T, class Alloc >
	void
	swap (vector<T,Alloc>& x, vector<T,Alloc>& y)	{

		x.swap(y);
	};

	template <class T, class Alloc>
	bool
	operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{

		if (lhs.size() != rhs.size())
			return false;
		if (lhs.front() != rhs.front() || lhs.back() != rhs.back())
			return false;
		return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
	};

	template <class T, class Alloc>
	bool
	operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return(!(lhs == rhs)); };


	template <class T, class Alloc>
	bool
	operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{

		return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

	};

	template <class T, class Alloc>
	bool
	operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return(!(lhs > rhs)); };

	template <class T, class Alloc>
	bool
	operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{

		return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

	};

	template <class T, class Alloc>
	bool
	operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)	{ return(!(lhs < rhs)); };

} // ----------------- ft namespace

#endif /* *****BVALETTE****** VECTOR_H */
