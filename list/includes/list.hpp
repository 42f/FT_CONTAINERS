#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <memory>
# include <string>
# include <iterator>
# include <limits>


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

			node( void ) : next(&(*this)), prev(&(*this)) {};
			node( T const & val ) : next(&(*this)), prev(&(*this)), data(val) {};

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
						position->prev->next = this;
					}
					position->prev = this;
				}
				if (DEBUG_MODE)
				{
					std::cout << __func__ << " at position: " << position << std::endl;
					putNodeInfos(*this);
				}
			};

			void
			unhook( void )	{

				if (prev != this)
					prev->next = next;
				if (next != this)
					next->prev = prev;
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

		private:
			node<T> *			_ptr;

			// iterator &	operator=(const iterator& rhs)  {
			// 	if (this != &rhs)
			// 		this->p = rhs.p;
			// 	return *this;
			// }
	};


	template< typename T, typename alloc = std::allocator<T> >
	class list {


		public:
			typedef node<T>							node;
			typedef iterator<T>						iterator;
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
			explicit list( void ) : _size(0) {

				_tail = createNode(value_type());
				_head = _tail;
				if (DEBUG_MODE)	{
					std::cout << std::endl;
					std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
				}
			};

			/**
			 * @brief fill Constructor
			*/
			explicit list( size_type n, value_type const & val = value_type(),
			allocator_type const & userAlloc = allocator_type() ) : _size(n), _alloc(userAlloc)	{

				_tail = createNode(val);
				_head = _tail;
				for (; n > 0; --n)
				{
					createNode(val)->hook(_head);
					_head = _head->prev;
				}
				if (DEBUG_MODE)
				{
					std::cout << "_head --> " << _head << std::endl;
					std::cout << "_tail --> " << _tail << std::endl;
					std::cout << "_size --> " << _size << std::endl;
				}
			};

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
					node *	cursor = _head;
					for (size_type i = 0; i < _size; i++)
					{
						if (cursor->next != cursor)	{
							cursor = cursor->next;
							_alloc.deallocate(cursor->prev, 1);
						}
						else	{
							_alloc.deallocate(cursor, 1);
							break ;
						}
					}
				}
				if (DEBUG_MODE)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			};

			size_type			max_size( void ) const	{ return size_type(-1) / sizeof(node);  };
			bool				empty( void ) const		{ return (_size == 0); };
			size_type			size( void ) const 		{ return (_size); };
			iterator			begin( void ) const		{ return (_head); };
			iterator			end( void ) const 		{ return (_tail); };
			// reverse_iterator	rbegin( void ) const	{ return (_tail); };
			// reverse_iterator	rend( void ) const 		{ return (_head); };
			reference			front( void ) const		{ return (_head->data); };
			reference			back( void ) const 		{ return (_tail->data); };

			void				pop_back ( void )	{

				if (_size > 0)	{
					node * tmpTail = _tail->prev;
					_tail->unhook();
					delete _tail;					// ?
					_tail = tmpTail;
					_size--;
				}
			};

			void				push_back (const value_type& val)	{

				if (_size > 0 && _size < max_size())	{
					node *	newTail = createNode(val);
					_tail->hook(newTail);
					_tail = newTail;
					_size++;
				}
				else if (_size == 0)
				{
					_tail->data = val;
					_size++;
				}
			};

		protected:
			node *		_head;
			node *		_tail;
			size_type		_size;
			allocator_type	_alloc;
		private:

			node * createNode(value_type const & val)	{

				node * pNewNode;
				try	{
					pNewNode = _alloc.allocate(1);
					_alloc.construct(pNewNode, val);
				}
				catch(const std::exception& e) {
					// delete liste ?

					std::cerr << e.what() << std::endl;
				}
				return pNewNode;
			};
	};

}

#endif /* *****BVALETTE****** LIST_H */
