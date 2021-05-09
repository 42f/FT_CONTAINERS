#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "map.hpp"
# include <iostream>
# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template< 	class Key,
				class T,
				class Compare,
				typename map_node>
	class mapIterator
	//  : public std::iterator< std::bidirectional_iterator_tag, T >
	{
		public:
			// typedef mapIterator<T, T_alloc>				iterator;
			// typedef const mapIterator<T, T_alloc>	 	const_iterator;

			typedef mapIterator<Key, T, Compare, map_node>			iterator;
			typedef mapIterator<Key, T, Compare, map_node> const	const_iterator;

			typedef	ft::pair<const Key, T>*					pointer;
			typedef	ft::pair<const Key, T>&					reference;
			typedef	const ft::pair<const Key, T>*			const_pointer;
			typedef	const ft::pair<const Key, T>&			const_reference;

			typedef map_node*								map_node_ptr;

			typedef ptrdiff_t								distance;

			mapIterator( void ) : _ptr(NULL) {
				if (DEBUG_MODE >= 1) std::cout << __func__ << " DFLT " << _ptr << std::endl;
			}
			mapIterator(map_node* src) : _ptr(src), _comp(Compare()) {
				if (DEBUG_MODE >= 1) std::cout << __func__ << " COPY " << _ptr << std::endl;
			}
			mapIterator(const iterator& itSrc) : _ptr(itSrc._ptr) {}

			void
			getNextBranch( void )	{

				Key				startKey = _ptr->item->first;
				map_node_ptr	cursor = _ptr->parent;

				while (cursor != NULL && _comp(cursor->item->first, startKey) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}

			void
			getPreviousBranch( void )	{

				Key				startKey = _ptr->item->first;
				map_node_ptr	cursor = _ptr->parent;

				while (cursor != NULL && _comp(startKey, cursor->item->first) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}


			iterator&
			operator++( void ) {

				if (isLeaf(_ptr) == true)	{
					if (_ptr == _ptr->parent->left)
						_ptr = _ptr->parent;
					else
						getNextBranch();
				}
				else	{
					if (_ptr->right != NULL)
						_ptr = getFarLeft(_ptr->right);
					else
						getNextBranch();
				}
				return *this;
			}

			iterator
			operator++( int ) {
				iterator tmp(*this);
				operator++();
				return tmp;
			}

			iterator&
			operator--( void ) {

				if (isLeaf(_ptr) == true)	{
					if (_ptr == _ptr->parent->right)
						_ptr = _ptr->parent;
					else
						getPreviousBranch();
				}
				else	{
					if (_ptr->left != NULL)
						_ptr = getFarRight(_ptr->left);
					else
						getPreviousBranch();
				}
				return *this;
			}

			iterator
			operator--( int ) {
				iterator tmp(*this);
				operator--();
				return tmp;
			}

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

			pointer
			operator->()				{ return (_ptr->item); }

			const_pointer
			operator->()	const		{ return (_ptr->item); }

			reference
			operator*()					{ return (*(_ptr->item)); }

			const_reference
			operator*()	const			{ return (*(_ptr->item)); }

			bool
			isLeaf(map_node_ptr node)	{
				return (node->left == NULL && node->right == NULL);
			}

			/**
			 * @brief Pointer holding the address of the iterator element.
			*/

			map_node_ptr		_ptr;
			Compare				_comp;




			map_node*
			getFarLeft( map_node* cursor )	{

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			map_node*
			getFarRight( map_node* cursor )	{

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}





	}; //----------------- Class iterator

} // ----------------- ft namespace

#endif
