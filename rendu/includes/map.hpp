#ifndef MAP_HPP
# define MAP_HPP

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

	template< typename TKey, typename TVal>
	struct btreeNodeBase	{

		typedef		TKey							key_type;
		typedef		TVal							value_type;
		typedef		btreeNodeBase *					base_pointer;
		typedef		typename std::pair<TKey, TVal>	nodePair_type;

		base_pointer 		left;
		nodePair_type		nodePair;
		base_pointer 		right;

		btreeNodeBase() : left(*this), nodePair(key_type(), value_type()), right(*this)	{};
		btreeNodeBase(nodePair_type pairSrc) : left(*this), nodePair(pairSrc), right(*this)	{};
		~btreeNodeBase() {};
	};		// btreeNode

	template< 	class TKey,
				class TVal,
				class Compare,
				class T_alloc>
	class btree	{

		public:

			typedef	typename std::pair<TKey, TVal>							pair_type;
			typedef	typename btreeNodeBas<TKey, TVal>						node_type;
			typedef typename T_alloc::template rebind<btreeNodeBase<TKey, TVal>::other
			allocator_type;

			typedef typename T_alloc::reference								reference;
			typedef typename T_alloc::const_reference						const_reference;
			typedef typename T_alloc::pointer								pointer;
			typedef typename T_alloc::const_pointer							const_pointer;

			btree( void ) : head(NULL), size(0), alloc(allocator_type()) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
				initStorage();
			}

			btree( allocator_type const & userAlloc ) : head(NULL), size(0), alloc(userAlloc) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> defaut with alloc " << __func__ << std::endl;
				initStorage();
			}

			btree( btree const & src ) : head(NULL), size(0), alloc(allocator_type()) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;
			}

			btree( btree const & src, allocator_type const & userAlloc ) : head(src.head), size(src.size), alloc(userAlloc) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> copy with alloc " << __func__ << std::endl;
			}

			~btree( void )	{

				deleteStorage();
				if (DEBUG_MODE >= 2) std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			pointer			head;
			size_t			size;
			allocator_type	alloc;

			void
			insertNode( pair_type pairSrc, pointer position = head )	{

				if (size == 0)	{
					alloc.construct(head, pairSrc);
				}
				else if (Compare(position->nodePair.first, pairSrc.first) == true ) {

					if (position->left != position)	{
						insert(p, position->left)
					}
					else	{
						position->left = alloc.allocate(1);
						alloc.construct(position->left, pairSrc.first, pair.second);
						incSize();
					}
				}
				else if (Compare(position->nodePair.first, pairSrc.first) == false &&
					nodePair.first != pairSrc.first)

					if (position->right != position)	{
						insert(p, position->right)
					}
					else	{
						position->right = alloc.allocate(1);
						alloc.construct(position->left, pairSrc.first, pair.second);
						incSize();
					}
			}

		protected:

			void
			initStorage( void )	{

				this->head = this->alloc.allocate(1);
			}

		private:

			void
			incSize( void ) { size++; }

			void
			decSize( void ) { size--; }

			void
			deleteStorage( void )	{
				// this->alloc.deallocate(head, n);
				if (DEBUG_MODE >= 2) std::cout << __func__ << std::endl;
			}

		}; // ----------------- Classbtree
/*
	template< typename T, class T_alloc = std::allocator<T> >
	class mapIterator : public std::iterator< std::random_access_iterator_tag, T >
	{
		public:
			typedef mapIterator<T, T_alloc>			iterator;
			typedef const mapIterator<T, T_alloc> 	const_iterator;
			typedef ptrdiff_t							distance;
			typedef typename T_alloc::reference			reference;
			typedef typename T_alloc::const_reference	const_reference;
			typedef typename T_alloc::pointer			pointer;
			typedef typename T_alloc::const_pointer		const_pointer;

			mapIterator( void ) :_ptr(NULL) {}
			mapIterator(T* src) :_ptr(src) {}
			mapIterator(const iterator& itSrc) : _ptr(itSrc._ptr) {}

			iterator&
			operator++( void ) {
				_ptr++;
				return *this;
			}

			iterator
			operator++( int ) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}

			iterator&
			operator--( void ) {
				_ptr--;
				return *this;
			}

			iterator
			operator--( int ) {
				iterator tmp(*this);
				operator--();
				return tmp;
			}

			distance
			operator- ( iterator rhs ) { return this->_ptr - rhs._ptr; }

			iterator
			operator- ( distance n ) {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			const_iterator
			operator- ( distance n ) const {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			iterator
			operator+ ( distance n ) {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			const_iterator
			operator+ ( distance n ) const {

				iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			void
			operator-= ( distance n )				{ *this = *this - n; }

			void
			operator+= ( distance n )				{ *this = *this + n; }

			bool
			operator==(const iterator& rhs) const	{ return _ptr==rhs._ptr; }

			bool
			operator!=(const iterator& rhs) const	{ return _ptr!=rhs._ptr; }

			bool
			operator<(const iterator& rhs) const	{ return _ptr< rhs._ptr; }

			reference
			operator*()								{ return *_ptr; }

			const_reference
			operator*()	const						{ return *_ptr; }
*/
			/**
			 * @brief Pointer holding the address of the iterator element.
			*/
/*			pointer		_ptr;

	}; //----------------- Class iterator
*/
	template< 	class TKey,
				class TVal,
				class Compare = std::less<TKey>,
				class T_alloc = std::allocator<btreeNodeBase<TKey, TVal> > >
	class map {

		private:
			typedef btree<TKey, TVal, Compare, T_alloc>		btree;
		public:
			typedef TKey									key_type;
			typedef TVal									value_type;
   			typedef typename T_alloc::allocator_type		allocator_type;
			typedef typename T_alloc::reference				reference;
			typedef typename T_alloc::const_reference		const_reference;
			typedef typename T_alloc::pointer				pointer;
			typedef typename T_alloc::const_pointer			const_pointer;
			typedef mapIterator<T>							iterator;
			typedef const mapIterator<T>					const_iterator;
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
			explicit map( allocator_type const & userAlloc = allocator_type() ) : btree(userAlloc) {

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> DEFAULT " << __func__ << std::endl;
			}

			/**
			 * @brief fill Constructor, allocate at least n memory blocks and
			 * construct n objects val.
			*/
			explicit map( size_type n, value_type const & val = value_type(),
				allocator_type const & userAlloc = allocator_type() ) : btree(n, userAlloc)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
				initFillmap(n, val);
			}

			/**
			 * @brief Range Constructor
			*/
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				 allocator_type const & userAlloc = allocator_type() )
				 : btree(userAlloc)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range pre dispatcher ! " << __func__ << std::endl;

				typename std::__is_integer<InputIterator>::__type	integer;
				map_constructor_dispatch(first, last, userAlloc, integer);
			}

			/**
			 * @brief Copy Constructor
			*/
			explicit map( map const & src ) : btree(src.size()) {

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;

				fillmap(src.begin(), src.end());
			}

			~map( void )	{

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

// 			size_type
// 			max_size( void ) const	{ return this->alloc.max_size();  }

// 			bool
// 			empty( void ) const		{ return (size() == 0); }

// 			size_type
// 			size( void ) const 		{ return (this->tail - this->head); }

// 			iterator
// 			begin( void ) 			{ return (this->head); }

// 			const_iterator
// 			begin( void ) const		{ return (this->head); }

// 			iterator
// 			end( void ) 	 		{ return (this->tail); }

// 			const_iterator
// 			end( void ) const 		{ return (this->tail); }

// 			reverse_iterator
// 			rbegin( void ) 			{ return reverse_iterator(end()); }

// 			const_reverse_iterator
// 			rbegin( void ) const	{ return reverse_iterator(end()); }

// 			reverse_iterator
// 			rend( void ) 	 		{ return reverse_iterator(begin()); }

// 			const_reverse_iterator
// 			rend( void ) const 		{ return reverse_iterator(begin()); }

// 			reference
// 			front( void ) 			{ return (*(this->head)); }

// 			const_reference
// 			front( void ) const		{ return (*(this->head)); }

// 			reference
// 			back( void ) 	 		{ return (*(this->tail - 1)); }

// 			const_reference
// 			back( void ) const 		{ return (*(this->tail - 1)); }

// 			size_type
// 			capacity( void ) const	{ return (this->tailStorage - this->head); }

// 			void
// 			pop_back( void )		{ if (size() > 0) erase(--end()); }

// 			void
// 			push_back (value_type const & val)	{ insert(end(), val); }

// 			void
// 			clear( void )			{ erase(begin(), end()); }

// 			/**
// 			 * @brief insert single element
// 			*/
// 			iterator insert(iterator position, const value_type& val)	{

// 				difference_type indexPos = position - begin();
// 				insert(position, 1, val);
// 				return begin() + indexPos; 		// to change
// 			}

// 			/**
// 			 * @brief insert n elements of val
// 			*/
// 			void insert (iterator position, size_type n, const value_type& val)	{

// 				if (capacity() == 0)	{
// 					this->initStorage(1);
// 					position = begin();
// 				}

// 				difference_type indexPos = position - begin();
// 				if (size() + n >= capacity())	{
// 					doReserve(capacity() + n + (capacity()>>1));
// 				}

// 				if (begin() + indexPos != end())	{
// 					if (size() > 1)	{
// 						memMoveRight(begin() + indexPos, end(), n);
// 					}
// 					destroyObjects(this->head + indexPos, size() - indexPos);
// 					this->tail += n;
// 					constructObjects(this->head + indexPos, n, val);
// 				}
// 				else {
// 					constructObjects(this->tail, n, val);
// 					this->tail += n;
// 				}
// 			}


// 			reference
// 			at (size_type n)	{
// 				checkRange(n);
// 				return ((*this)[n]);
// 			}

// 			const_reference
// 			at (size_type n) const	{
// 				checkRange(n);
// 				return ((*this)[n]);
// 			}

// 			/**
// 			 * @brief insert range of elements
// 			 * check here if arguments of type InputIterator are integer
// 			 * or iterators and dispatch to the right overload.
// 			 * Cf. /usr/include/c++/7/bits/cpp_type_traits.h line 136
// 			 * for implementation. Basicly __is_integer is a template function
// 			 * which, by default containts __false_type as __type, unless
// 			 * it is one of the integer types so it contains __true_type
// 			 * Here we create integer wich will be of type __true_type
// 			 * or __false_type, and by calling insert_dispatch with it, the right
// 			 * overload is called.
// 			*/
// 			template <class InputIterator>
// 			void
// 			insert (iterator position, InputIterator first,
// 			InputIterator last)	{

// 				typename std::__is_integer<InputIterator>::__type	integer;
// 				insert_dispatch(position, first, last, integer);
// 			}

// 			iterator
// 			erase (iterator position)	{

// 				destroyObjects(position._ptr, 1);
// 				memMoveLeft(position + 1, end(), 1);
// 				this->tail -= 1;
// 				return position;
// 			}

// 			iterator
// 			erase (iterator first, iterator last)	{

// 				size_type			offset = first - begin();
// 				difference_type		len = last - first;
// 				destroyObjects(first._ptr, len);
// 				memMoveLeft(last, end(), len);
// 				this->tail -= len;
// 				return begin() + offset;
// 			}

// 			void
// 			resize (size_type n, value_type val = value_type())	{

// 				if (n < size())	{
// 					erase(end() - (size() - n), end());
// 				}
// 				else if (n > size())	{
// 					insert(end(), n - size(), val);
// 				}
// 			}

// 			void
// 			swap (map& src)	{

// 				pointer 	headTmp = src.head;
// 				pointer 	tailTmp = src.tail;
// 				pointer		tailStorageTmp = src.tailStorage;

// 				src.head = this->head;
// 				src.tail = this->tail;
// 				src.tailStorage = this->tailStorage;

// 				this->head = headTmp;
// 				this->tail = tailTmp;
// 				this->tailStorage = tailStorageTmp;
// 			}

// 			/**
// 			 * @brief Here we use the same technic as for insert : the type
// 			 *  integer is  used to call the right overload.
// 			*/
// 			template <class InputIterator>
// 			void assign (InputIterator first, InputIterator last)	{

// 				typename std::__is_integer<InputIterator>::__type	integer;
// 				assign_dispatch(first, last, integer);
// 			}

// 			void assign(size_type n, const value_type& val)	{

// 				clear();
// 				insert(begin(), n, val);
// 			}

// 			/**
// 			 * @brief Reserve: Requests that the map capacity be at
// 			 * least enough to contain n elements.
// 			*/
// 			void
// 			reserve (size_type n) {

// 				if (n > max_size())	{
// 					throw std::length_error("ft::map::reserve called with n > max_size");
// 				}
// 				else	{
// 					doReserve(n);
// 				}
// 			}

// 			map&
// 			operator= (const map& x)	{

// 				if (*this != x)
// 					assign(x.begin(), x.end());
// 				return *this;
// 			}

// 			reference
// 			operator[] (size_type n)	{
// 				return (*(this->head + n));
// 			}

// 			const_reference
// 			operator[] (size_type n) const	{
// 				return (*(this->head + n));
// 			}

// /******************************************************************************.
// .******************************************************************************.
// .*********** PRIVATE MEMBER FUNCTIONS AND HELPERS  ****************************.
// .******************************************************************************.
// .******************************************************************************/

// 		private:

// 			template <class InputIterator>
// 			void
// 			assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

// 				clear();
// 				insert(begin(), first, last);
// 			}

// 			template<typename integer>
// 			void
// 			assign_dispatch (integer n, integer val, std::__true_type)	{

// 				assign(static_cast<size_type>(n), static_cast<value_type>(val));
// 			}


// 			/**
// 			 * @brief Fill Constructor actual function
// 			*/
// 			template <class integer>
// 			void
// 			map_constructor_dispatch (integer n, integer const & val,
// 				allocator_type const &, std::__true_type)	{

// 				if (DEBUG_MODE >= 1)	{
// 					std::cout << "dispatch --> __true_type " << __func__ << std::endl;
// 					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
// 				}
// 				this->initStorage(n);
// 				initFillmap(n, val);
// 			}

// 			/**
// 			 * @brief Range Constructor actual function
// 			*/
// 			template <class InputIterator>
// 			void
// 			map_constructor_dispatch (InputIterator first, InputIterator last,
// 				 allocator_type const &, std::__false_type)	{

// 				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range : " << __func__ << std::endl;

// 				size_t	n = std::distance(first, last);
// 				this->initStorage(n * 2);
// 				fillmap(first, last);
// 			}


// 			template<typename integer>
// 			void
// 			insert_dispatch(iterator position, integer n, integer val,
// 			std::__true_type)	{
// 				insert(position, static_cast<size_type>(n),
// 					static_cast<value_type>(val));
// 			}

// 			template<typename InputIterator>
// 			void
// 			insert_dispatch(iterator position, InputIterator first,
// 			InputIterator last, std::__false_type)	{

// 				if (capacity() == 0)	{
// 					this->initStorage(1);
// 					position = begin();
// 				}

// 				difference_type indexPos = position - begin();
// 				size_type		n = last - first;
// 				if (size() + n >= capacity())	{
// 					doReserve(capacity() + n + (capacity()>>1));
// 				}

// 				if (begin() + indexPos != end())	{
// 					if (size() > 1)	{
// 						memMoveRight(begin() + indexPos, end(), n);
// 					}
// 					destroyObjects(this->head + indexPos, size() - indexPos);
// 					this->tail += n;
// 					constructObjects(this->head + indexPos, first, last);
// 				}
// 				else {
// 					constructObjects(this->head + indexPos, first, last);
// 					this->tail += n;
// 				}
// 			}

// 			/**
// 			 * @brief Construct objects at alocated memory, to be used by
// 			 * constructors
// 			*/
// 			void
// 			fillmap(iterator first, iterator last)	{

// 				for (;first != last; first++)	{
// 					this->alloc.construct(this->tail, *first);
// 					this->tail++;
// 					if (this->tail == this->tailStorage)
// 						std::cout << "RESIZE HERE" << std::endl;			// not fixed yet
// 				}
// 			}

// 			/**
// 			 * @brief Construct objects at alocated memory, to be used by
// 			 * constructors
// 			*/
// 			void
// 			initFillmap(size_type n, value_type const & val)	{

// 				this->tail = this->head + n;
// 				for (size_t i = 0; i < n; i++){
// 					this->alloc.construct(this->head + i, val);
// 				}
// 			}



// 			/**
// 			 * @brief doReserve: No throw version of Reserve.
// 			*/
// 			void
// 			doReserve (size_type n) {

// 				if (n > this->capacity())	{
// 					pointer		oldHead = this->head;
// 					size_type	oldSize = this->size();
// 					size_type	oldCapacity = this->capacity();

// 					reallocateBigger(n);

// 					destroyObjects(oldHead, oldSize);
// 					this->alloc.deallocate(oldHead, oldCapacity);
// 				}
// 			}

// 			void
// 			reallocateBigger(size_type n)	{

// 				if (n > this->capacity())	{

// 					iterator	oldHeadIt = begin();
// 					iterator	oldTailIt = end();

// 					this->initStorage(n);
// 					constructObjects(this->head, oldHeadIt, oldTailIt);
// 					this->tail += oldTailIt - oldHeadIt;
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, size_t n, value_type val = value_type())	{
// 				for (size_t i = 0; i < n; i++)	{
// 					this->alloc.construct(p + i, val);
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, iterator first, iterator last)	{
// 				for (size_t i = 0; first != last; i++, first++)	{
// 					this->alloc.construct(p + i, *first);
// 				}
// 			}

// 			void
// 			destroyObjects(pointer p, size_t n)	{
// 				for (size_t i = 0; i < n; i++)	{
// 					this->alloc.destroy(p + i);
// 				}
// 			}

// 			void
// 			clearObject( void )	{

// 				if (DEBUG_MODE >= 3) std::cout << __func__ << std::endl;
// 				destroyObjects(this->head, this->size());
// 			}

// 			/**
// 			 * @brief Move [first, last] range by n memory blocks to theLeft
// 			*/
// 			void
// 			memMoveLeft(iterator first, iterator last, size_t n)	{			// to be tested
// 				while (first != last)	{
// 					constructObjects(first._ptr - n, 1, *first);
// 					destroyObjects(first._ptr, 1);
// 					first++;
// 				}
// 			}


// 			/**
// 			 * @brief Move [first, last] range by n memory blocks to the right
// 			*/
// 			void
// 			memMoveRight(iterator first, iterator last, size_t n)	{
// 				while (last != first)	{
// 					last--;
// 					constructObjects(last._ptr + n, 1, *last);
// 					destroyObjects(last._ptr, 1);
// 				}
// 			}

// 			void
// 			checkRange(size_type n)	const {
// 				if (n > size())	{
// 					throw std::out_of_range("Out of map's range");
// 				}
// 			}
		}; // ----------------- Class map

		// template <class T, class Alloc >
		// void
		// swap (map<T,Alloc>& x, map<T,Alloc>& y)	{

		// 	x.swap(y);
		// };

		// template <class T, class Alloc>
		// bool
		// operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	if (lhs.size() != rhs.size())
		// 		return false;
		// 	if (lhs.front() != rhs.front() || lhs.back() != rhs.back())
		// 		return false;
		// 	return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		// };

		// template <class T, class Alloc>
		// bool
		// operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs == rhs)); };


		// template <class T, class Alloc>
		// bool
		// operator<  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

		// };

		// template <class T, class Alloc>
		// bool
		// operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs > rhs)); };

		// template <class T, class Alloc>
		// bool
		// operator>  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

		// };

		// template <class T, class Alloc>
		// bool
		// operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs < rhs)); };
} // ----------------- ft namespace
#endif /* *****BVALETTE****** MAP_HPP */
