#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "../utils/ft_iterator_base.hpp"
# include "../utils/ft_rev_iterator.hpp"
# include "../utils/ft_enable_if.hpp"

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

	template< typename T, bool B>
	class vector_iterator : public ft::iterator< ft::random_access_iterator_tag, T, B>
	{
		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, B>	iterator;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::reference								reference;
            typedef typename iterator::pointer									pointer;

			vector_iterator( void ) :_ptr(NULL) {}
			vector_iterator(T* src) :_ptr(src) {}
			vector_iterator(const vector_iterator& itSrc) : _ptr(itSrc.getPtr()) {}
			~vector_iterator( void ) {}

			vector_iterator&
			operator=( const vector_iterator& src )	{
				if (*this != src)	{
					_ptr = src.getPtr();
				}
				return (*this);
			}

			vector_iterator&
			operator++( void ) {
				_ptr++;
				return *this;
			}

			vector_iterator
			operator++( int ) {
				vector_iterator tmp(*this);
				operator++();
				return tmp;
			}

			vector_iterator&
			operator--( void ) {
				_ptr--;
				return *this;
			}

			vector_iterator
			operator--( int ) {
				vector_iterator tmp(*this);
				operator--();
				return tmp;
			}

			difference_type
			operator- ( vector_iterator rhs ) { return this->_ptr - rhs._ptr; }

			vector_iterator
			operator- ( difference_type n ) {

				vector_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			vector_iterator
			operator- ( difference_type n ) const {

				vector_iterator tmpIt = *this;
				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

			vector_iterator
			operator+ ( difference_type n ) {

				vector_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			vector_iterator
			operator+ ( difference_type n ) const {

				vector_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

			void		operator-=( difference_type n )				{ *this = *this - n; }
			void		operator+=( difference_type n )				{ *this = *this + n; }
			bool		operator==(const vector_iterator& rhs) const	{ return _ptr==rhs._ptr; }
			bool		operator!=(const vector_iterator& rhs) const	{ return _ptr!=rhs._ptr; }
			bool		operator<(const vector_iterator& rhs) const		{ return _ptr < rhs._ptr; }
			bool		operator>(const vector_iterator& rhs) const		{ return _ptr > rhs._ptr; }
			bool		operator<=(const vector_iterator& rhs) const	{ return _ptr <= rhs._ptr; }
			bool		operator>=(const vector_iterator& rhs) const	{ return _ptr >= rhs._ptr; }

			reference	operator[]( size_t n )	const					{ return _ptr[n]; }

			pointer		operator->()	const							{ return _ptr; }
			reference	operator*()	const								{ return *_ptr; }

			pointer		getPtr( void )	const							{ return _ptr; }

		private:

			/**
			 * @brief Pointer holding the address of the vector_iterator element.
			*/
			pointer		_ptr;

	}; //----------------- Class iterator

} // ----------------- ft namespace

#endif /* *****BVALETTE****** VECTOR_H */
