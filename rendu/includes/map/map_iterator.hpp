#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "../utils/ft_pair.hpp"
# include "../utils/ft_enable_if.hpp"
# include "../utils/ft_rev_iterator.hpp"
# include <iostream>
# include <cstddef>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template< 	class Key,
				class T,
				class Compare,
				typename map_node, bool B>
	class map_iterator	{

		public:
            typedef std::bidirectional_iterator_tag				iterator_category;
			typedef std::ptrdiff_t								difference_type;

			typedef ft::reverse_iterator< map_iterator<Key, T, Compare, map_node, false> >	reverse_iterator;
			typedef ft::reverse_iterator< map_iterator<Key, T, Compare, map_node, true> >	const_reverse_iterator;
			// typedef std::reverse_iterator< map_iterator<Key, T, Compare, map_node, false> >	reverse_iterator;
			// typedef std::reverse_iterator< map_iterator<Key, T, Compare, map_node, true> >	const_reverse_iterator;

			typedef	Compare									key_compare;
			typedef typename ft::pair<const Key, T>			value_type;
			typedef typename ft_enable_if<B, value_type&, const value_type&>::type       reference;
            typedef typename ft_enable_if<B, value_type*, const value_type*>::type       pointer;


			map_iterator( map_node* ptr = NULL, map_node* dumbNode = NULL,
				const key_compare& comp = key_compare() ) :	_ptr(ptr),
															_btreeDumdNode(dumbNode),
															_comp(comp)		{}


			map_iterator(const map_iterator<Key, T, Compare, map_node, false>& itSrc) :	_ptr(itSrc.getPtr()),
																						_btreeDumdNode(itSrc.getDumbNode()),
																						_comp(itSrc.getComp())		{}

			~map_iterator( void )	{}

			map_iterator&
			operator++( void ) {

				if (_ptr == _btreeDumdNode)
					_ptr = _btreeDumdNode->left;
				else if (isLastNode(_ptr) == true)
					_ptr = _btreeDumdNode;
				else if (isLeaf(_ptr) == true)	{
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

			map_iterator
			operator++( int ) {
				map_iterator tmp(*this);
				operator++();
				return tmp;
			}

			map_iterator&
			operator--( void ) {

				if (_ptr == _btreeDumdNode)
					_ptr = _btreeDumdNode->right;
				else if (isFirstNode(_ptr) == true)
					_ptr = _btreeDumdNode;
				else if (isLeaf(_ptr) == true)	{
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

			map_iterator
			operator--( int ) {
				map_iterator tmp(*this);
				operator--();
				return tmp;
			}

			bool
			operator==(const map_iterator& rhs) const	{ return _ptr==rhs.getPtr(); }

			bool
			operator!=(const map_iterator& rhs) const	{ return _ptr!=rhs.getPtr(); }

			bool
			operator<(const map_iterator& rhs) const	{ return _ptr< rhs.getPtr(); }

			pointer
			operator->()	const		{ return (&_ptr->item); }

			reference
			operator*()	const		{ return (_ptr->item); }


			map_node*			getPtr(void) const { return (_ptr);	}
			// map_node*			getPosParent(void) const {

			// 	if (_ptr != NULL)
			// 		return (_ptr->parent);
			// 	return (NULL);
			// }

			map_node*			getDumbNode(void) const { return (_btreeDumdNode);	}
			Compare				getComp(void) const { return (_comp);	}


		private:
			/**
			 * @brief Pointer holding the address of the map_iterator element.
			*/
			map_node*			_ptr;
			map_node*			_btreeDumdNode;
			Compare				_comp;

			void
			getNextBranch( void )	{

				Key				startKey = _ptr->item.first;
				map_node*		cursor = _ptr->parent;

				while (cursor != NULL && _comp(cursor->item.first, startKey) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}

			void
			getPreviousBranch( void )	{

				Key				startKey = _ptr->item.first;
				map_node*		cursor = _ptr->parent;

				while (cursor != NULL && _comp(startKey, cursor->item.first) == true)
					cursor = cursor->parent;
				_ptr = cursor;
			}

			static	map_node*
			getFarLeft( map_node* cursor )	{

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			static	map_node*
			getFarRight( map_node* cursor )	{

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}

			bool
			isFirstNode( map_node* p )	{
				return (p == _btreeDumdNode->left);
			}

			bool
			isLastNode( map_node* p )	{
				return (p == _btreeDumdNode->right);
			}

			static	bool
			isLeaf(map_node* node)	{
				return (node->left == NULL && node->right == NULL);
			}


		}; //----------------- Class map_iterator


} // ----------------- ft namespace

#endif
