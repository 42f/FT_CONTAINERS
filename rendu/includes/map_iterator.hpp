#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "map.hpp"
# include <iostream>
# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	// template< typename T, class T_alloc = std::allocator<T> >
	template< 	class Key,
				class T,
				class Compare,
				typename map_node>
	class mapIterator : public std::iterator< std::bidirectional_iterator_tag, T >
	{
		public:
			// typedef mapIterator<T, T_alloc>				iterator;
			// typedef const mapIterator<T, T_alloc>	 	const_iterator;

			typedef mapIterator<Key, T, Compare, map_node>			iterator;
			typedef mapIterator<Key, T, Compare, map_node> const	const_iterator;
			typedef ptrdiff_t							distance;
			// typedef typename T_alloc::reference			reference;
			// typedef typename T_alloc::const_reference	const_reference;
			// typedef typename T_alloc::pointer			pointer;
			// typedef typename T_alloc::const_pointer		const_pointer;

			typedef	map_node*							pointer;
			typedef	map_node&							reference;
			typedef	const map_node*						const_pointer;
			typedef	const map_node&						const_reference;

			mapIterator( void ) : _ptr(NULL) {
				if (DEBUG_MODE >= 1) std::cout << __func__ << " " << _ptr << std::endl;
			}
			mapIterator(pointer src) : _ptr(src) {
				if (DEBUG_MODE >= 1) std::cout << __func__ << " " << _ptr << std::endl;
			}
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

			// iterator&
			// operator--( void ) {
			// 	_ptr--;
			// 	return *this;
			// }

			// iterator
			// operator--( int ) {
			// 	iterator tmp(*this);
			// 	operator--();
			// 	return tmp;
			// }

			// distance
			// operator- ( iterator rhs ) { return this->_ptr - rhs._ptr; }

			// iterator
			// operator- ( distance n ) {

			// 	iterator tmpIt = *this;

			// 	while ( n > 0 )	{
			// 		tmpIt--;
			// 		n--;
			// 	}
			// 	return tmpIt;
			// }

			// const_iterator
			// operator- ( distance n ) const {

			// 	iterator tmpIt = *this;

			// 	while ( n > 0 )	{
			// 		tmpIt--;
			// 		n--;
			// 	}
			// 	return tmpIt;
			// }

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

			// void
			// operator-= ( distance n )				{ *this = *this - n; }

			void
			operator+= ( distance n )				{ *this = *this + n; }

			bool
			operator==(const iterator& rhs) const	{ return _ptr==rhs._ptr; }

			bool
			operator!=(const iterator& rhs) const	{ return _ptr!=rhs._ptr; }

			bool
			operator<(const iterator& rhs) const	{ return _ptr< rhs._ptr; }

			reference
			operator*()								{ return _ptr->pair; }

			const_reference
			operator*()	const						{ return _ptr->pair; }

			// reference
			// operator*()								{ return _ptr; }

			// const_reference
			// operator*()	const						{ return _ptr; }

			/**
			 * @brief Pointer holding the address of the iterator element.
			*/

			pointer		_ptr;
	}; //----------------- Class iterator

} // ----------------- ft namespace

#endif
