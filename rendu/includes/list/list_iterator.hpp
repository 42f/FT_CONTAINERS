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

			typedef typename	ft::node<T>			node;

		public:

			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T, B>					iterator;
			typedef typename iterator::value_type				value_type;
			typedef typename iterator::difference_type			difference_type;
			typedef typename iterator::difference_type			Distance;
			typedef typename iterator::reference					reference;
            typedef typename iterator::pointer					pointer;
			// typedef T																		value_type;
			// typedef std::ptrdiff_t															difference_type;
			// typedef typename	ft::ft_enable_if<B, value_type&, const value_type&>::type	reference;
            // typedef typename	ft::ft_enable_if<B, value_type*, const value_type*>::type	pointer;

			list_iterator( void ) :_ptr(NULL) {}
			list_iterator(node* src) :_ptr(src) {}
			list_iterator(const list_iterator& itSrc) : _ptr(itSrc._ptr) {}

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

			difference_type	operator- ( list_iterator rhs ) {

				difference_type		ret = 0;
				if (rhs < *this)	{
					while (*this != rhs && rhs._ptr != rhs._ptr->next)	{
						ret++;
						rhs++;
					}
				}
				return ret;
			}

			list_iterator	operator- ( difference_type n ) {

				list_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			list_iterator	operator+ ( difference_type n ) {

				list_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			void	operator-= ( difference_type n ) {

				*this = *this - n;
			}

			void	operator+= ( difference_type n ) {

				*this = *this + n;
			}

			bool 		operator==(const list_iterator& rhs) const { return _ptr==rhs._ptr; }
			bool 		operator!=(const list_iterator& rhs) const { return _ptr!=rhs._ptr; }
			bool 		operator<(const list_iterator& rhs) const {

				if (*this == rhs)
					return false;
				list_iterator	tmpIt = *this;
				while (tmpIt._ptr != tmpIt._ptr->next && tmpIt != rhs)
					tmpIt++;
				return (tmpIt == rhs);
			}

			T &	operator*() { return _ptr->data; }

			node*				_ptr;

	}; //----------------- Classlist_iterator

} // ----------------- ft namespace

#endif

