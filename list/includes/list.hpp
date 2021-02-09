#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <memory>
# include <string>
# include <iterator>
# include <limits>
# include <algorithm>


#ifndef DEBUG_MODE
# define DEBUG_MODE false
#endif

namespace ft	{

	template< typename T>
	class node	{

		public:
			node<T>	*next;
			node<T>	*prev;
			T		data;

			node( void ) : next(this), prev(this) {

				if (DEBUG_MODE)
					std::cout << "CONSTRUCTOR --> " << __func__ << std::endl;

			};
			node( T const & val ) : next(this), prev(this), data(val) {

				if (DEBUG_MODE)
				{
					std::cout << "CONSTRUCTOR with Param--> " << __func__ << std::endl;
					std::cout << __func__ << " this: " << this << std::endl;
					std::cout << __func__ << " prev: " << prev << std::endl;
					std::cout << __func__ << " next: " << next << std::endl;
				}
			};

			~node( void )	{
				if (DEBUG_MODE)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			};

			// static void
			// swap(node& x, node& y)	{

			// };

			// void
			// transfer(node * const first, node * const last)	{


			// };

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
					next = position;
					if (position->prev != position)
					{
						prev = position->prev;
						prev->next = this;
					}
					position->prev = this;
				}
				if (DEBUG_MODE)
				{
					std::cout << __func__ << " at position: " << position << std::endl;
					std::cout << __func__ << " prev = " << prev << std::endl;
					std::cout << __func__ << " next = " << next << std::endl;
					putNodeInfos(*this);
				}
			};

			void
			unhook( void )	{

				if (prev != this && next != this)	{
					next->prev = prev;
					prev->next = next;
				}
				else if (prev == this)
					next->prev = next;
				else if (next == this)
					prev->next = prev;
			};

			static void	putNodeInfos(node<T> const &n) {
				std::cout << std::endl;
				std::cout << "--NODE: " << &n << std::endl;
				std::cout << "data -> " << n.data << " @ " << &(n.data) << std::endl;
				std::cout << "prev -> " << n.prev << std::endl;
				std::cout << "next -> " << n.next << std::endl;
				std::cout << std::endl;
			};
	};

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
	};


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

				_tail = getNode(value_type());
				_head = _tail;
				if (DEBUG_MODE)	{
					std::cout << std::endl;
					std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
					std::cout << "\t_head --> " << _head << std::endl;
					std::cout << "\t_tail --> " << _tail << std::endl;
					std::cout << "\t_size --> " << _size << std::endl;
				}
			};

			/**
			 * @brief fill Constructor
			*/
			explicit list( size_type n, value_type const & val = value_type(),
				allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc)	{

				_tail = getNode(val);
				_head = _tail;
				for (; n > 0; --n)
					push_back(val);
			};


//do insert first
			// template <class InputIterator>
			// list (InputIterator first, InputIterator last,
			// 	 allocator_type const & userAlloc = allocator_type() ) : _size(0), _alloc(userAlloc)	{

			// 	while( first != last )	{
			// 		this->push_back(*first);
			// 		first++;
			// 	}
			// };

			/**
			 * @brief Copy Constructor
			*/
			explicit list( list const & src ) : _size(0) {

				if (*this != src){
						// copy
				}

				if (DEBUG_MODE)	{
					std::cout << std::endl;
					std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;
				}
			};

			~list( void )	{

				if (_size != 0)	{
					node *	cursor = _tail;
					for (size_type i = 0; cursor != _head; i++)
					{
						cursor = cursor->prev;
						_alloc.destroy(cursor->next);
						_alloc.deallocate(cursor->next, 1);
					}
					_alloc.destroy(_head);
					_alloc.deallocate(_head, 1);
				}
				if (DEBUG_MODE)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			};











			size_type			max_size( void ) const	{ return size_type(-1) / sizeof(node);  };
			bool				empty( void ) const		{ return (_size == 0); };
			size_type			size( void ) const 		{ return (_size); };
			iterator			begin( void ) const		{ return (_head); };
			iterator			end( void ) const 		{ return (_tail); };
			reverse_iterator	rbegin( void ) const	{ return reverse_iterator(end()); };
			reverse_iterator	rend( void ) const 		{ return reverse_iterator(begin()); };
			reference			front( void ) const		{ return (_head->data); };
			reference			back( void ) const 		{ return (_tail->data); };
















			void
			pop_back( void )	{

				if (_size > 0)	{
					node * cursor = _tail->prev;
					if (cursor == _head)
						_head = _tail;
					cursor->unhook();
					_alloc.destroy(cursor);
					_alloc.deallocate(cursor, 1);
					decSize();
				}
			};

			void
			push_back (value_type const & val)	{

				insert(end(), val);
			};

			void
			pop_front( void )	{

				if (_size > 0)	{
					node * cursor = _head->next;
					_head->unhook();
					_alloc.destroy(_head);
					_alloc.deallocate(_head, 1);
					_head = cursor;
					decSize();
				}
			};

			void
			push_front (value_type const & val)	{

				insert(begin(), val);
			};







			/**
			 * @brief assign range
			*/
			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last)	{


			//   };
			// void assign (size_type n, const value_type& val)	{

			// 	iterator it = begin();
			// 	for (iterator it = begin(); it != end(); ++it, --n)
			// 		*it = val;
			// 	if (n > 0)
			// 		isnert(end(), n, val);
			// 	else
			// 		erase(it, end());
			// };






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

				for(; n > 0; --n)	{
					insert(position, val);
				}
			};

			iterator
			erase (iterator position)	{

std::cout << __func__ << " called it " << std::endl;
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

				node * returnCursor = last._ptr;
				for (; first != last; first++)
					erase(first);
				return returnCursor;
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
















		protected:
			node *		_head;
			node *		_tail;
			size_type		_size;
			allocator_type	_alloc;

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

		private:

			void	incSize( void )	{ _size++; }
			void	decSize( void )	{ _size--; }

			node * getNode(value_type const & val)	{

				node * newNode;
				try	{
					newNode = _alloc.allocate(1);
					_alloc.construct(newNode, val);
					newNode->next = newNode;
					newNode->prev = newNode;
				}
				catch(const std::exception& e) {
					// delete liste ?

					std::cerr << e.what() << std::endl;
				}
				if (DEBUG_MODE)
					std::cout << "Create " << val << " @ " << newNode << std::endl;
				return newNode;
			};
	};

}

#endif /* *****BVALETTE****** LIST_H */
