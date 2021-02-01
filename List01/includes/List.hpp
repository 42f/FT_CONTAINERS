#ifndef LIST_HPP
# define LIST_HPP

# include <iostream>
# include <memory>
# include <string>


template< typename T>
class Node	{

	public:
		T	  	data;
		Node *	prev;
		Node *	next;
};

namespace ft {

	template< typename T, class Alloc = std::allocator<T> >
	class List
	{

		public:
			typedef T								value_type;
			typedef typename Alloc::template rebind<Node<T> >::other	allocator;
			typedef size_t							size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef typename Alloc::reference		reference;
			typedef typename Alloc::const_reference	const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;

			typedef std::forward_iterator_tag		iterator_categor;

			class iterator : public std::iterator< std::input_iterator_tag, T >
			{
				public:
					iterator(Node<T>* x) :_p(x) {}
					iterator(const iterator& mit) : _p(mit._p) {}

					iterator&	operator++( void ) {
						_p = _p->next;
						return *this;
					}

					iterator 	operator++( int ) {
						iterator tmp(*this);
						operator++();
						return tmp;
					}

					bool 		operator==(const iterator& rhs) const { return _p==rhs.p; }
					bool 		operator!=(const iterator& rhs) const { return _p!=rhs.p; }

					T* 			operator*() { return *_p; }

				private:
					Node<T>*			_p;

					iterator &	operator=(const iterator& rhs)  {
						if (this != &rhs)
							this->p = rhs.p;
						return *this;
					}
			};

			List( void ) : _head(NULL), _tail(NULL), _size(0) {};
			List( size_type n, value_type val) : _head(NULL), _tail(NULL), _size(n) {

				Node *	cursor = NULL;
				for (size_type i = 0; i < n; i++)
				{
					if (i == 0)
					{
						try	{ cursor = _allocator.allocate(1); }
						catch ( std::exception & e) { std::cerr << e.what() << std::endl; }
						this->_head = cursor;
						cursor->prev = NULL;
					}
					else
					{
						try	{ cursor->next = _allocator.allocate(1); }
						catch ( std::exception & e) { std::cerr << e.what() << std::endl; }
						cursor->next->prev = cursor;
						cursor = cursor->next;
					}
					cursor->data = val + i;
					cursor->next = NULL;
				}
				this->_tail = cursor;
			};

			~List( void ) {

				Node *	cursor = this->_head;
				for (size_type i = 0; i < this->_size; i++)
				{
					if (cursor->next != NULL)	{
						cursor = cursor->next;
						_allocator.deallocate(cursor->prev, 1);
					}
					else	{
						_allocator.deallocate(cursor, 1);
					}
				}
			};

			unsigned int	getSize( void ) const { return (this->_size); };
			iterator		front( void ) const { return (this->_head); };
			iterator		back( void ) const { return (this->_tail); };

			List<T> &		operator=( List<T> const & rhs );
			List<T>( List const & src );

			Node<T> *		_head;
			Node<T> *		_tail;
			unsigned int	_size;
		private:
			typedef Node<T>		Node;
			allocator	_allocator;

	};
};

template< typename T>
std::ostream &			operator<<( std::ostream & o, ft::List<T> const & i )	{

	o << "head -> " << i._head << std::endl;
	o << "size -> " << i._size << std::endl;
	o << "tail -> " << i._tail << std::endl << std::endl;
	Node<T> * cursor = i._head;
	for (unsigned int i = 0; cursor != NULL; i++)
	{
		std::cout << "prev : " << cursor->prev << std::endl;
		std::cout << "curr : " << cursor << std::endl;
		std::cout << "data : " << cursor->data << std::endl;
		std::cout << "next : " << cursor->next << std::endl << std::endl;
		cursor = cursor->next;
	}

	return o;
};

#endif /* *****BVALETTE****** LIST_H */
