#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <memory>
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

			};
			node( T const & val ) : next(this), prev(this), data(val) {

				if (DEBUG_MODE >= 3)
				{
					std::cout << "CONSTRUCTOR with Param--> " << __func__ << std::endl;
					std::cout << __func__ << " this: " << this << std::endl;
					std::cout << __func__ << " prev: " << prev << std::endl;
					std::cout << __func__ << " next: " << next << std::endl;
				}
			};

			~node( void )	{
				if (DEBUG_MODE >= 2)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			};

			static void
			swap(node& x, node& y)	{

				node	*posx = x.next;
				node	*posy = y.next;
				y.unhook();
				y.hook(posx);
				x.unhook();
				x.hook(posy);

			};

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
			};

			void
			reverse( void )	{

				node *tmp;
				tmp = next;
				next = prev;
				prev = tmp;
			};

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

		};

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
			};

			// ---------------------------------------------------------------------------------------TO REMOVE
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
			};
		}; // ----------------- Class node

	template< typename T, class Alloc = std::allocator<T> >
	class iterator : public std::iterator< std::bidirectional_iterator_tag, T >
	{
		public:
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

			bool 		operator==(const iterator& rhs) const { return _ptr==rhs._ptr; }
			bool 		operator!=(const iterator& rhs) const { return _ptr!=rhs._ptr; }

			T &	operator*() { return _ptr->data; }

		// private:
			node<T> *			_ptr;

			// iterator &	operator=(const iterator& rhs)  {
			// 	if (this != &rhs)
			// 		_ptr = rhs.ptr;
			// 	return *this;
			// }
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
				_tail = getNode(value_type());
				_head = _tail;
			};

			/**
			 * @brief fill Constructor
			*/
			explicit list( size_type n, value_type const & val = value_type(),
				allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc)	{

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;

				initFillList(n, val);
			};


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

			};

			/**
			 * @brief Copy Constructor
			*/
			explicit list( list const & src ) : _size(0) {

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;
				_tail = getNode(value_type());
				_head = _tail;
				_alloc = src._alloc;

				// if (*this != src){						//								ADD BACK
				if (src.size() > 0)
					assign(src.begin(), src.end());

			};

			~list( void )	{

				clear();
				if (_head != NULL)	{
					_alloc.destroy(_head);
					_alloc.deallocate(_head, 1);
				}
				if (DEBUG_MODE >= 1)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			};

			size_type			max_size( void ) const	{ return _alloc.max_size();  };
			bool				empty( void ) const		{ return (_size == 0); };
			size_type			size( void ) const 		{ return (_size); };
			iterator			begin( void ) const		{ return (_head); };
			iterator			end( void ) const 		{ return (_tail); };
			reverse_iterator	rbegin( void ) const	{ return reverse_iterator(end()); };
			reverse_iterator	rend( void ) const 		{ return reverse_iterator(begin()); };
			reference			front( void ) const		{ return (_head->data); };
			reference			back( void ) const 		{ return (_tail->data); };

			list&
			operator= (const list& x)	{

				// if (*this != x)											// to add back !
					assign(x.begin(), x.end());
				return *this;
			};

			void
			pop_back( void )						{ erase(--end()); };
			void
			push_back (value_type const & val)		{ insert(end(), val); };
			void
			pop_front( void )						{ erase(begin()); };
			void
			push_front (value_type const & val)		{ insert(begin(), val); };

			void
			clear( void )	{ erase(begin(), end()); };


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
			};

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
			};

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
			};

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
			};


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
			};

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
			};

			/**
			 * @brief Here we use the same technic as for insert : the type
			 *  integer is  used to call the right overload.
			*/
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last)	{

				typename std::__is_integer<InputIterator>::__type	integer;
				assign_dispatch(first, last, integer);
			};

			void assign(size_type n, const value_type& val)	{

				clear();
				insert(begin(), n, val);
			};

		/**
		 *	@brief entire list (1)
		*/
			void
			splice (iterator position, list& x)	{

				splice(position, x, x.begin(), x.end());
			};

		/**
		 *	@brief single element (2)
		*/
			void
			splice (iterator position, list& x, iterator it)	{

				if (x.size() > 0)	{
					iterator	tmpItNext = it;
					tmpItNext++;
					it._ptr->unhook();
					it._ptr->hook(position._ptr);
					if (position._ptr == _head)
						_head = it._ptr;

					if (it._ptr == x._head)
						x._head = tmpItNext._ptr;

					if (x.size() == 1)
						x._head = x._tail;
					this->incSize();
				}
				x.decSize();
			};

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
			};











		protected:
			node *			_head;
			node *			_tail;
			size_type		_size;
			allocator_type	_alloc;

		private:

			void	incSize( size_type n = 1 )	{ _size += n; }
			void	decSize( size_type n = 1 )	{ _size -= n; }

			template <class InputIterator>
			void
			assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

				clear();
				insert(begin(), first, last);
			};

			template<typename integer>
			void
			assign_dispatch (integer n, integer val, std::__true_type)	{

				assign(static_cast<size_type>(n), static_cast<value_type>(val));
			};


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
			};

			/**
			 * @brief Range Constructor actual function
			*/
			template <class InputIterator>
			void
			list_constructor_dispatch (InputIterator first, InputIterator last,
				 allocator_type const & userAlloc, std::__false_type)	{

				if (DEBUG_MODE >= 1)
					std::cout << "CONSTRUCTOR --> range " << __func__ << std::endl;
				_size = 0;
				_alloc = userAlloc;
				_tail = getNode(value_type());
				_head = _tail;
				insert(begin(), first, last);
			};


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

				_tail = getNode(value_type());
				_head = _tail;
				insert(begin(), n, val);
			}

			node*
			getNode(value_type const & val)	{

				node * newNode;
				try	{
					newNode = _alloc.allocate(1);
					_alloc.construct(newNode, val);
					newNode->next = newNode;
					newNode->prev = newNode;
				}
				catch(const std::exception& e) {
					//			------------------------------------------------- delete liste ?

					std::cerr << e.what() << std::endl;
				}
				if (DEBUG_MODE >= 2)
					std::cout << "Create " << val << " @ " << newNode << std::endl;
				return newNode;
			};
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
