#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "../utils/ft_enable_if.hpp"
# include "../utils/ft_iterator_base.hpp"
# include "../utils/ft_rev_iterator.hpp"
# include "../utils/ft_node.hpp"

# include <iostream>
# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template< typename T, bool B >
	class list_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T, B>
	{

		private:

			typedef typename ft::node<T>		node;

		public:

			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T, B>	iterator;
			typedef typename iterator::value_type								value_type;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::reference								reference;
            typedef typename iterator::pointer									pointer;

			typedef  node&		node_reference;
			typedef  node*		node_pointer;

			list_iterator( node_pointer src = NULL ) :_ptr(src) {}

			list_iterator( const list_iterator<T, true>& src ) { _ptr = src.getPtr(); }
			list_iterator( const list_iterator<T, false>& src ) { _ptr = src.getPtr(); }

			~list_iterator( void ) {}

			list_iterator&
			operator=( const list_iterator<T, Node, true>& src ) {
					_ptr = src.getPtr();
				return (*this);
			}

			list_iterator&
			operator=( const list_iterator<T, Node, false>& src ) {
					_ptr = src.getPtr();
				return (*this);
			}

			list_iterator&	operator++( void ) {
				_ptr = _ptr->next;
				return *this;
			}

			list_iterator 	operator++( int ) {
				list_iterator tmp(*this);
				operator++();
				return tmp;
			}

			list_iterator&	operator--( void ) {
				_ptr = _ptr->prev;
				return *this;
			}

			list_iterator 	operator--( int ) {
				list_iterator tmp(*this);
				operator--();
				return tmp;
			}

			bool 		operator==(const list_iterator& rhs) const 					{ return _ptr==rhs.getPtr(); }
			bool 		operator!=(const list_iterator& rhs) const 					{ return _ptr!=rhs.getPtr(); }

			pointer		operator->()	const	{ return &(_ptr->data); }
			reference	operator*()		const	{ return _ptr->data; }


		private:

			node_pointer		getPtr(void) const 		{ return (_ptr);	}
			node_pointer		_ptr;

	}; //----------------- Classlist_iterator

} // ----------------- ft namespace

#endif

