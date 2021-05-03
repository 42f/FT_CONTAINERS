#ifndef LIST_HPP
# define LIST_HPP

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

	template< typename T>
	class node	{

		public:
			node<T>	*next;
			node<T>	*prev;
			T		data;

			node( void ) : next(this), prev(this) {

				if (DEBUG_MODE >= 2)
					std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;

			}
			node( T const & val ) : next(this), prev(this), data(val) {

				if (DEBUG_MODE >= 3)
				{
					std::cout << "CONSTRUCTOR with Param--> " << __func__ << std::endl;
					std::cout << __func__ << " this: " << this << std::endl;
					std::cout << __func__ << " prev: " << prev << std::endl;
					std::cout << __func__ << " next: " << next << std::endl;
				}
			}

			~node( void )	{
				if (DEBUG_MODE >= 2)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			static void
			swap(node& x, node& y)	{

				if (&x != &y)	{
					node *posx;
					if (&y != x.next)
						posx = x.next;
					else
						posx = &x;
					node	*posy = y.next;
					y.unhook();
					y.hook(posx);
					x.unhook();
					x.hook(posy);
				}
			}

			void
			transfer(node * const first, node * const last)	{

				if (first != last)	{
					node *	beforeLast = last->prev;
					if (first->prev != first)	{
						first->prev->next = last;
						last->prev = first->prev;
						first->prev = first;
					}
					else
						last->prev = last;
					beforeLast->next = beforeLast;
				}
				if (DEBUG_MODE >= 3)
					putNodeInfos(*this);
			}

			void
			hook(node * const position)	{

				if (position != NULL)	{

					if (position->prev != position)
					{
						this->prev = position->prev;
						this->prev->next = this;
					}
					if (this->next == this)
					{
						this->next = position;
						position->prev = this;
					}
					else	{
						node * cursor = this;
						while (cursor->next != cursor)
							cursor = cursor->next;
						cursor->next = position;
						position->prev = cursor;
					}

					if (DEBUG_MODE >= 3)
					{
						std::cout << __func__ << " at position: " << position << std::endl;
						std::cout << __func__ << " prev = " << prev << std::endl;
						std::cout << __func__ << " next = " << next << std::endl;
						putNodeInfos(*this);
					}
				}
			}

			void
			unhook( void )	{

			if (DEBUG_MODE >= 3)
				putNodeInfos(*this);

				if (prev != this && next != this)	{
					next->prev = prev;
					prev->next = next;
				}
				else if (prev == this)
					next->prev = next;
				else if (next == this)
					prev->next = prev;
				this->next = this;
				this->prev = this;
			if (DEBUG_MODE >= 3)
				putNodeInfos(*this);
			}

			static void	putNodeInfos(node<T> const &n) {
				std::cout << std::endl;
				std::cout << "--NODE: " << &n << std::endl;
				std::cout << "data -> " << n.data << " @ " << &(n.data) << std::endl;
				std::cout << "prev -> " << n.prev << std::endl;
				std::cout << "next -> " << n.next << std::endl;
				if (n.next != &(n))
					putNodeInfos(*n.next);
				else
					std::cout << std::endl;
			}
		}; // ----------------- Class node

	template< typename T, class Alloc = std::allocator<T> >
	class iterator : public std::iterator< std::bidirectional_iterator_tag, T >
	{
		public:
			typedef ptrdiff_t	distance;
			iterator( void ) :_ptr(NULL) {}
			iterator(node<T>* src) :_ptr(src) {}
			iterator(const iterator& itSrc) : _ptr(itSrc._ptr) {}

			iterator&	operator++( void ) {
				_ptr = _ptr->next;
				return *this;
			}

			iterator 	operator++( int ) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}

			iterator&	operator--( void ) {
				_ptr = _ptr->prev;
				return *this;
			}

			iterator 	operator--( int ) {
				iterator tmp(*this);
				operator--();
				return tmp;
			}

			distance	operator- ( iterator rhs ) {

				distance		ret = 0;
				if (rhs < *this)	{
					while (*this != rhs && rhs._ptr != rhs._ptr->next)	{
						ret++;
						rhs++;
					}
				}
				return ret;
			}

			iterator	operator- ( distance n ) {

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

			void	operator-= ( distance n ) {

				*this = *this - n;
			}

			void	operator+= ( distance n ) {

				*this = *this + n;
			}

			bool 		operator==(const iterator& rhs) const { return _ptr==rhs._ptr; }
			bool 		operator!=(const iterator& rhs) const { return _ptr!=rhs._ptr; }
			bool 		operator<(const iterator& rhs) const {

				if (*this == rhs)
					return false;
				iterator	tmpIt = *this;
				while (tmpIt._ptr != tmpIt._ptr->next && tmpIt != rhs)
					tmpIt++;
				return (tmpIt == rhs);
			}

			T &	operator*() { return _ptr->data; }

			node<T> *			_ptr;

	}; //----------------- Class iterator


	template< typename T, typename alloc = std::allocator<T> >
	class list {


		public:
			typedef node<T>							node;
			typedef iterator<T>						iterator;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			// typedef const_iterator<T>						const_iterator;
			// typedef std::const_reverse_iterator<iterator>	const_reverse_iterator;
			typedef T								value_type;
			typedef size_t							size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef typename alloc::reference		reference;
			typedef typename alloc::const_reference	const_reference;
			typedef typename alloc::pointer			pointer;
			typedef typename alloc::const_pointer	const_pointer;
			typedef typename alloc::template rebind<node>::other	allocator_type;


			/**
			 * @brief Default Constructor
			*/
			explicit list( allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc) {

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> DEFAULT " << __func__ << std::endl;
				initFillList(0, value_type());
			}

			/**
			 * @brief fill Constructor
			*/
			explicit list( size_type n, value_type const & val = value_type(),
				allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc)	{

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
				initFillList(n, val);
			}


			/**
			 * @brief Range Constructor
			*/
			template <class InputIterator>
			list (InputIterator first, InputIterator last,
				 allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc)	{

				typename std::__is_integer<InputIterator>::__type	integer;
				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> range pre dispatcher ! " << __func__ << std::endl;
				list_constructor_dispatch(first, last, userAlloc, integer);
			}

			/**
			 * @brief Copy Constructor
			*/
			explicit list( list const & src ) : _head(NULL), _tail(NULL), _size(0) {

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;

				initFillList(0, value_type());
				if (src.size() > 0)
					assign(src.begin(), src.end());
			}

			~list( void )	{

				clearObject();
				if (DEBUG_MODE >= 1)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			size_type			max_size( void ) const	{ return _alloc.max_size();  }
			bool				empty( void ) const		{ return (_size == 0); }
			size_type			size( void ) const 		{ return (_size); }
			iterator			begin( void ) const		{ return (_head); }
			iterator			end( void ) const 		{ return (_tail); }
			reverse_iterator	rbegin( void ) const	{ return reverse_iterator(end()); }
			reverse_iterator	rend( void ) const 		{ return reverse_iterator(begin()); }
			reference			front( void ) 			{ return (_head->data); }
			reference			back( void ) 	 		{ return (_tail->prev->data); }
			const_reference		front( void ) const		{ return (_head->data); }
			const_reference		back( void ) const 		{ return (_tail->prev->data); }

			list&
			operator= (const list& x)	{

				if (*this != x)
					assign(x.begin(), x.end());
				return *this;
			}

			void
			pop_back( void )						{ erase(--end()); }
			void
			push_back (value_type const & val)		{ insert(end(), val); }
			void
			pop_front( void )						{ erase(begin()); }
			void
			push_front (value_type const & val)		{ insert(begin(), val); }

			void
			clear( void )	{ erase(begin(), end()); }


			/**
			 * @brief insert single element
			*/
			iterator insert(iterator position, const value_type& val)	{

				node *	newNode = getNode(val);
				if (_size < max_size())	{
					if (_head == _tail || position == begin())
						_head = newNode;
					newNode->hook(position._ptr);
					incSize();
				}
				return newNode;
			}

			/**
			 * @brief insert n elements of val
			*/
			void insert (iterator position, size_type n, const value_type& val)	{

				if (n + _size <= max_size())
				{
					for(; n > 0; --n)	{
						insert(position, val);
					}
				}
			}

			/**
			 * @brief insert range of elements
			 * check here if arguments of type InputIterator are integer
			 * or iterators and dispatch to the right overload.
			 * Cf. /usr/include/c++/7/bits/cpp_type_traits.h line 136
			 * for implementation. Basicly __is_integer is a template function
			 * which, by default containts __false_type as __type, unless
			 * it is one of the integer types so it contains __true_type
			 * Here we create integet wich will be of type __true_type
			 * or __false_type, and by calling inster_dispatch with it, the right
			 * overload is called.
			 * insert_dispatch taking __true_type will execute code for
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

				node * cursor = position._ptr;
				node * returnCursor = cursor->next;
				if (_size > 0)	{
					if (cursor == _head)
						_head = _head->next;
					cursor->unhook();
					_alloc.destroy(cursor);
					_alloc.deallocate(cursor, 1);
					decSize();
				}
				return returnCursor;
			}

			iterator
			erase (iterator first, iterator last)	{

				iterator tmpCursor = first;
				while (first != last)
				{
					tmpCursor = first;
					first++;
					erase(tmpCursor);
				}
				return last;
			}


			void
			resize (size_type n, value_type val = value_type())	{

				if (n < _size)	{
					typename ft::list<T>::iterator it = begin();
					for(size_type i = 0; i < n; i++)
						it++;
					erase(it, end());
				}
				else if (n > _size)
					insert(end(), n - _size, val);
			}

			void
			swap (list& src)	{

				node *		_headTmp = src._head;
				node *		_tailTmp = src._tail;
				size_type	_sizeTmp = src._size;

				src._head = _head;
				src._tail = _tail;
				src._size = _size;

				_head = _headTmp;
				_tail = _tailTmp;
				_size = _sizeTmp;
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
		 *	@brief entire list (1)
		*/
			void
			splice (iterator position, list& x)	{

				splice(position, x, x.begin(), x.end());
			}

		/**
		 *	@brief single element (2)
		*/
			void
			splice (iterator position, list& x, iterator it)	{

				splice(position, x, it, ++it);
			}	// splice

		/**
		 *	@brief element range (3)
		*/
			void
			splice (iterator position, list& x, iterator first, iterator last)	{

				if (x.size() > 0)	{

					size_type sizeSplice = std::distance(first, last);

					first._ptr->transfer(first._ptr, last._ptr);
					first._ptr->hook(position._ptr);
					if (position._ptr == _head)
						_head = first._ptr;
					if (first._ptr == x._head)
						x._head = last._ptr;
					this->incSize(sizeSplice);
					x.decSize(sizeSplice);
					if (x.size() == 0)
						x._head = x._tail;
				}
			}	// splice


			void remove (const value_type& val)	{

				iterator	itFind = begin();

				while ((itFind = std::find(itFind, end(), val)) != end())
					itFind = erase(itFind);
			}	// remove

			template <class Predicate>
			void
			remove_if (Predicate pred)	{

				iterator	itFind = begin();

				while ((itFind = std::find_if(itFind, end(), pred)) != end())
					itFind = erase(itFind);
			}	// remove


			void
			unique( void )	{ unique(equality()); }

			template <class BinaryPredicate>
			void
			unique (BinaryPredicate binary_pred)	{

				iterator	itFind = begin();
				iterator	itEndGroup = begin();

				while ((itFind = std::adjacent_find(itEndGroup, end(), binary_pred)) != end())	{
					itEndGroup = itFind;
					while (binary_pred(*itFind, *itEndGroup) == true && itEndGroup != end())
						itEndGroup++;
				 	erase(++itFind, itEndGroup);
				}

			} // unique

			void merge (list& x)	{ merge(x, smaller_than()); }

			template <class Compare>
			void
			merge (list& x, Compare comp)	{

				if (*this == x)
					return ;
				iterator	thisCursor = this->begin();
				while (x.empty() == false)	{
					while (thisCursor != this->end() && comp(*x.begin(), *thisCursor) == false)	{
						thisCursor++;
					}
					this->splice(thisCursor, x, x.begin());
				}
				if (x.empty() == false)
					this->splice(this->end(), x);
			} // merge

			void sort() { sort(smaller_than()); }

			template <class Compare>
			void
			sort (Compare comp)	{

				std::sort(begin(), end(), comp);
			} // sort

			void
			reverse( void )	{


				node * lastElem = _tail->prev;
				node * newHead = lastElem;
				node::swap(*_head, *lastElem);
				_head = newHead;

				size_t		swapSize = ((size() / 2) % 2 == 0) ?
							((size() - 2) / 2) : ((size() - 2) / 2);

				iterator	it = begin() + 1;
				iterator	ite = end() - 2;
				iterator	tmpIt = it;
				iterator	tmpIte = ite;
				for (size_t i = 0; i < swapSize ; i++)	{

					tmpIt = it + 1;
					tmpIte = ite - 1;
					if (DEBUG_MODE >= 2)
						std::cout << "SWAP: " <<  *it << " ; " << *ite << std::endl;
					node::swap(*it._ptr, *ite._ptr);
					it = tmpIt;
					ite = tmpIte;
				}

			} // reverse

		protected:

			node *			_head;
			node *			_tail;
			size_type		_size;
			allocator_type	_alloc;

		private:

			void	incSize( size_type n = 1 )	{ _size += n; }
			void	decSize( size_type n = 1 )	{ _size -= n; }

			struct smaller_than {
				bool operator() (value_type const & a, value_type const & b) const
				{ return (a<b); }
			};

			struct equality {
				bool operator() (value_type const & a, value_type const & b) const
				{ return (a==b); }
			};


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
			list_constructor_dispatch (integer n, integer const & val,
				allocator_type const &, std::__true_type)	{

				if (DEBUG_MODE >= 1)	{
					std::cout << "dispatch --> __true_type " << __func__ << std::endl;
					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
				}
				initFillList(n, val);
			}

			/**
			 * @brief Range Constructor actual function
			*/
			template <class InputIterator>
			void
			list_constructor_dispatch (InputIterator first, InputIterator last,
				 allocator_type const & userAlloc, std::__false_type)	{

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> range " << __func__ << std::endl;
				_alloc = userAlloc;
				initFillList(0, value_type());
				insert(begin(), first, last);
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
				for (; first != last; ++first)	{
					insert(position, *first);
				}
			}

			/**
			 * @brief initialize the head and tail of a new list, to be
			 * used only by constructors.
			*/
			void
			initFillList(size_type n, value_type const & val)	{

				_size = 0;
				_head = _tail = NULL;
				_tail = getNode(value_type());
				_head = _tail;
				insert(begin(), n, val);
			}

			void
			clearObject( void )	{
				clear();
				if (_head != NULL)	{
					_alloc.destroy(_head);
					_alloc.deallocate(_head, 1);
				}
			}

			node*
			getNode(value_type const & val)	{

				node * newNode = NULL;
				try	{
					newNode = _alloc.allocate(1);
					_alloc.construct(newNode, val);
					newNode->next = newNode;
					newNode->prev = newNode;
				}
				catch(const std::exception& e) {
					clearObject();
					throw std::exception();
				}
				if (DEBUG_MODE >= 2)
					std::cout << "Create " << val << " @ " << newNode << std::endl;
				return newNode;
			}
		}; // ----------------- Class list

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


} // ----------------- ft namespace

#endif /* *****BVALETTE****** LIST_H */
