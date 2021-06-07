#ifndef DEQUE_ITERATOR_HPP
# define DEQUE_ITERATOR_HPP

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
	class deque_iterator : public ft::iterator< ft::random_access_iterator_tag, T, B>
	{
		friend class deque_iterator<T, !B>;

		private:

            typedef T				base_type;
            typedef base_type&		base_reference;
            typedef base_type*		base_pointer;

		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T, B>	iterator;
			typedef typename iterator::size_type								size_type;
			typedef typename iterator::difference_type							difference_type;
			typedef typename iterator::reference								reference;
            typedef typename iterator::pointer									pointer;

			deque_iterator( const base_pointer src = NULL ) :_ptr(src) {}
			deque_iterator( const deque_iterator<T, false>& itSrc )  :_ptr(itSrc.getPtr()) {}

			~deque_iterator( void ) {}

			deque_iterator&
			operator=( const deque_iterator& src )	{
				_ptr = src.getPtr();
				return (*this);
			}

			deque_iterator&
			operator++( void ) {
				_ptr++;
				return *this;
			}

		deque_iterator
			operator++( int ) {
				deque_iterator tmp(*this);
				operator++();
				return tmp;
			}

			deque_iterator&
			operator--( void ) {
				_ptr--;
				return *this;
			}

		deque_iterator
			operator--( int ) {
				deque_iterator tmp(*this);
				operator--();
				return tmp;
			}

			difference_type
			operator- ( const deque_iterator<T, true> rhs ) const	{ return this->_ptr - rhs.getPtr(); }
			difference_type
			operator- ( const deque_iterator<T, false> rhs ) const	{ return this->_ptr - rhs.getPtr(); }

		deque_iterator
			operator- ( difference_type n ) {

				deque_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

		deque_iterator
			operator- ( difference_type n ) const {

				deque_iterator tmpIt = *this;
				while ( n > 0 )	{
					tmpIt--;
					n--;
				}
				return tmpIt;
			}

		deque_iterator
			operator+ ( difference_type n ) {

				deque_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}

		deque_iterator
			operator+ ( difference_type n ) const {

				deque_iterator tmpIt = *this;

				while ( n > 0 )	{
					tmpIt++;
					n--;
				}
				return tmpIt;
			}


			deque_iterator&	operator-=( difference_type n )		{ *this = *this - n; return *this;}
			deque_iterator&	operator+=( difference_type n )		{ *this = *this + n; return *this;}

			bool		operator==(const deque_iterator<T, true>& rhs) const	{ return _ptr==rhs.getPtr(); }
			bool		operator!=(const deque_iterator<T, true>& rhs) const	{ return _ptr!=rhs.getPtr(); }
			bool		operator<(const deque_iterator<T, true>& rhs) const	{ return _ptr < rhs.getPtr(); }
			bool		operator>(const deque_iterator<T, true>& rhs) const	{ return _ptr > rhs.getPtr(); }
			bool		operator<=(const deque_iterator<T, true>& rhs) const	{ return _ptr <= rhs.getPtr(); }
			bool		operator>=(const deque_iterator<T, true>& rhs) const	{ return _ptr >= rhs.getPtr(); }

			bool		operator==(const deque_iterator<T, false>& rhs) const	{ return _ptr==rhs.getPtr(); }
			bool		operator!=(const deque_iterator<T, false>& rhs) const	{ return _ptr!=rhs.getPtr(); }
			bool		operator<(const deque_iterator<T, false>& rhs) const	{ return _ptr < rhs.getPtr(); }
			bool		operator>(const deque_iterator<T, false>& rhs) const	{ return _ptr > rhs.getPtr(); }
			bool		operator<=(const deque_iterator<T, false>& rhs) const	{ return _ptr <= rhs.getPtr(); }
			bool		operator>=(const deque_iterator<T, false>& rhs) const	{ return _ptr >= rhs.getPtr(); }

			reference	operator[]( size_type n )	const	{ return _ptr[n]; }

			pointer		operator->()	const				{ return _ptr; }
			reference	operator*()		const				{ return *_ptr; }

		private:

			base_pointer	getPtr( void )	const			{ return _ptr; }

			/**
			 * @brief Pointer holding the address of the deque_iterator element.
			*/
			base_pointer	_ptr;

	}; //----------------- Class iterator

	template<class T, bool B>
	deque_iterator<T, B>
	operator+ ( size_t n, deque_iterator<T, B>rhs ) {

		ft::deque_iterator<T,B> tmpIt = rhs;
		while ( n > 0 )	{
			tmpIt++;
			n--;
		}
		return tmpIt;
	}

} // ----------------- ft namespace

#endif /* *****BVALETTE****** VECTOR_H */
