#ifndef MAP_HPP
# define MAP_HPP

# include "../utils/ft_pair.hpp"
# include "map_iterator.hpp"

# include <iostream>
# include <memory>
# include <cstddef>
# include <string>
// # include <iterator>
# include <limits>
# include <algorithm>
# include <stdexcept>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

namespace ft	{

/*############################################################################*/
/*############################################################################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*###########################           MAP CLASS         ####################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*############################################################################*/
/*############################################################################*/


	template< 	class Key,
				class T,
				class Compare = std::less<Key>,
				class Allocator = std::allocator< ft::pair<const Key, T> > >
	class map {


/******************************************************************************.
.******************************************************************************.
.*********** MEMBER TYPES            ******************************************.
.******************************************************************************.
.******************************************************************************/
		private:
			struct	map_node;
		public:

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef	Compare									key_compare;

			typedef size_t									size_type;
			typedef std::ptrdiff_t							difference_type;

			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;


			typedef typename ft::map_iterator<Key, T, Compare, map_node, false>	iterator;
			typedef typename ft::map_iterator<Key, T, Compare, map_node, true>	const_iterator;

            // typedef typename std::reverse_iterator<map_iterator<Key, T, Compare, map_node, false> > reverse_iterator;
            // typedef typename std::reverse_iterator<map_iterator<Key, T, Compare, map_node, true> >  const_reverse_iterator;
            typedef typename ft::reverse_iterator<map_iterator<Key, T, Compare, map_node, false> > reverse_iterator;
            typedef typename ft::reverse_iterator<map_iterator<Key, T, Compare, map_node, true> >  const_reverse_iterator;

		private:
			typedef typename Allocator::template rebind<map_node>::other	_node_allocator_type;


/******************************************************************************.
.******************************************************************************.
.*********** NESTED CLASSES          ******************************************.
.******************************************************************************.
.******************************************************************************/

		private:

			struct map_node	{

				map_node( value_type itemSrc ) :	left(NULL),
													parent(NULL),
													right(NULL),
													item(itemSrc) {}
				~map_node( void ) {}

				map_node*		left;
				map_node*		parent;
				map_node*		right;
				value_type		item;
				bool			color;
			};

		public:

			class value_compare	{

				friend class map<Key, T, Compare, Allocator>;
				public:
					typedef	bool		result_type;
					typedef	value_type	first_argument_type;
					typedef	value_type	second_argument_type;

					bool
					operator()( const value_type& lhs, const value_type& rhs ) const {
						return (_comp(lhs.first, rhs.first));
					}

				protected:
					value_compare( Compare c ) : _comp(c) {}

					Compare				_comp;
			};

/******************************************************************************.
.******************************************************************************.
.*********** CONSTRUCTORS DESTRUCTOR           ********************************.
.******************************************************************************.
.******************************************************************************/


		public:
			/**
			 * @brief Default Constructor
			*/
			explicit
			map( const Compare& comp = key_compare(),
			const allocator_type & userAlloc = allocator_type() )	: 	_head(NULL),
																		_dumbNode(NULL),
																		_size(0),
																		_allocNode(userAlloc),
																		_comp(comp)				{
				if (DEBUG_MODE >= 4) std::cout << "CONSTRUCTOR --> DEFAULT explicit " << __func__ << std::endl;
			}


			/**
			 * @brief Range Constructor
			*/
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& userAlloc = allocator_type() ) :	_head(NULL),
																		_dumbNode(NULL),
																		_size(0),
																		_allocNode(userAlloc),
																		_comp(comp)				{

				if (DEBUG_MODE >= 4) std::cout << "CONSTRUCTOR --> range pre dispatcher ! " << __func__ << std::endl;
				insert(first, last);
			}

			/**
			 * @brief Copy Constructor
			*/
			map( map const & src ) :	_head(NULL),
												_dumbNode(NULL),
												_size(0),
												_allocNode(src._allocNode),
												_comp(src._comp)				{

				if (DEBUG_MODE >= 4) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;

				insert(src.begin(), src.end());
			}


			~map( void )	{

				if (DEBUG_MODE >= 4) std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
				clear();
			}

/******************************************************************************.
.******************************************************************************.
.*********** PRIVATE VARIABLES  ***********************************************.
.******************************************************************************.
.******************************************************************************/

			protected:
				map_node*				_head;
				map_node*				_dumbNode;
				size_t					_size;
				_node_allocator_type 	_allocNode;
				Compare	const			_comp;

/******************************************************************************.
.******************************************************************************.
.*********** 🚧  DEBUG 🚧             ******************************************.
.******************************************************************************.
.******************************************************************************/

			// private:
			public:
				void
				debugPrintTree()	{

					if (DEBUG_MODE < 2)
						return ;
					std::cout << "***********************************" << std::endl;
					std::cout << __func__ << "_head is pointing to:  " << _head << std::endl;
					std::cout << "_dumbNode is... : " << std::endl;
					debugPrintNode(_dumbNode);
					std::cout << "Printing tree of size  " << _size << std::endl;

					std::cout << "****************ITERATORES*******************" << std::endl;
					iterator it = begin();
					iterator ite = end();

					for(; it != ite; ++it)	{
						debugPrintNode(it.getPtr());
					}
					std::cout << "***********************************" << std::endl;
				}

				static void
				debugPrintNode( map_node* node )	{

					if (DEBUG_MODE < 2)
						return ;
					if (node != NULL)	{
						std::cout << std::endl;
						std::cout << __func__ << std::endl;
						std::cout << "NODE   " << node << std::endl;
						std::cout << "--- KEY    " << node->item.first << std::endl;
						std::cout << "--  VAL    " << node->item.second << std::endl;
						std::cout << "parent " << node->parent;
						if (node->parent != NULL)
							std::cout << "(" << node->parent->item.first << ";" << node->parent->item.second << ")" << std::endl;
						else
							std::cout << "--> THIS NODE IS _HEAD" << std::endl;

						std::cout << " left   " << node->left;
						if (node->left != NULL)
							std::cout << "(" << node->left->item.first << ";" << node->left->item.second << ")";
						std::cout << std::endl;
						std::cout << " right  " << node->right;
						if (node->right != NULL)
							std::cout << "(" << node->right->item.first << ";" << node->right->item.second << ")";
						std::cout << std::endl;
						std::cout << std::endl;
					}
					else
						std::cout << __func__ << "Called with null" << std::endl;

				}

/******************************************************************************.
.******************************************************************************.
.*********** PUBLIC MEMBER FUNCTIONS ******************************************.
.******************************************************************************.
.******************************************************************************/

		public:

			iterator
			find (const key_type& k)	{

				if (empty() == true)
					return(iterator());
				map_node*	nodeFound = locateNode(_head, k);
				if (nodeFound == NULL)
					return (end());
				return (iterator(nodeFound, _dumbNode, _comp));
			}

			const_iterator
			find (const key_type& k) const	{

				if (empty() == true)
					return(iterator());
				map_node* const	nodeFound = locateNode(_head, k);
				if (nodeFound == NULL)
					return (end());
				return (const_iterator(nodeFound, _dumbNode, _comp));
			}

			size_type
			count (const key_type& k) const	{
				return (find(k) != end() ? 1 : 0);
			}

			iterator
			lower_bound (const key_type& k) {

				if (empty() == true)
					return(iterator());

				map_node* const	nodeFound = locateBound(_head, k, isLowerBoundNode);

				if (nodeFound == NULL)
					return (end());
				else
					return (iterator(nodeFound, _dumbNode, _comp));
			}

			const_iterator
			lower_bound (const key_type& k) const	{

				if (empty() == true)
					return(const_iterator());

				map_node* const	nodeFound = locateBound(_head, k, isLowerBoundNode);

				if (nodeFound == NULL)
					return (end());
				else
					return (const_iterator(nodeFound, _dumbNode, _comp));
			}


			iterator
			upper_bound (const key_type& k) {

				if (empty() == true)
					return(iterator());

				map_node* const	nodeFound = locateBound(_head, k, isUpperBoundNode);

				if (nodeFound == NULL)
					return (end());
				else
					return (iterator(nodeFound, _dumbNode, _comp));
			}

			const_iterator
			upper_bound (const key_type& k) const	{

				if (empty() == true)
					return(const_iterator());

				map_node* const	nodeFound = locateBound(_head, k, isUpperBoundNode);

				if (nodeFound == NULL)
					return (end());
				else
					return (const_iterator(nodeFound, _dumbNode, _comp));
			}


			pair<iterator,iterator>
			equal_range (const key_type& k)	{

				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			pair<const_iterator, const_iterator>
			equal_range (const key_type& k) const	{

				return (ft::make_pair(lower_bound(k), upper_bound(k)));
			}

			size_type
			max_size( void ) const	{ return this->_allocNode.max_size(); }

			bool
			empty( void ) const		{ return (_size == 0); }

			size_type
			size( void ) const 		{ return (_size); }

			iterator
			begin( void ) 			{
				if (_dumbNode != NULL)
					return (iterator(_dumbNode->left, _dumbNode, _comp));
				return (iterator());
			}

			iterator
			begin( void ) const		{
				if (_dumbNode != NULL)
					return (iterator(_dumbNode->left, _dumbNode, _comp));
				return (iterator());
			}

			iterator
			end( void ) 	 		{
				if (_dumbNode != NULL)
					return (iterator(_dumbNode, _dumbNode, _comp));
				return (iterator());
			}

			iterator
			end( void ) const 		{
				if (_dumbNode != NULL)
					return (iterator(_dumbNode, _dumbNode, _comp));
				return (iterator());
			}

			reverse_iterator
			rbegin( void ) 			{	return reverse_iterator(--end());	}

			const_reverse_iterator
			rbegin( void ) 	const	{	return reverse_iterator(--end());	}

			reverse_iterator
			rend( void ) 			{	return reverse_iterator(end());	}

			const_reverse_iterator
			rend( void ) 	const	{	return reverse_iterator(end());	}

			void
			clear( void )			{

				if (DEBUG_MODE >= 3) std::cout << __func__ << std::endl;
				freeAllNodes(_head);
				freeNode(_dumbNode);
				_size = 0;
				_head = NULL;
				_dumbNode = NULL;
			}

			/**
			 * @brief insert single element
			*/
			ft::pair<iterator, bool>
			insert(const value_type& val)	{
				return(btree_insert_data(NULL, &_head, val));
			}


			/**
			 * @brief insert single element with hint to determine a closer
			 * insertion point
			*/
			iterator
			insert (iterator position, const value_type& val)	{

				map_node* posPtr = position.getPtr();

				if (position == NULL)
					return (iterator());

				std::cout << "VALUE IS ----------------------- " << val.first << std::endl;
				if (locateBound(position.getPtr(), val.first, isLowerBoundNode) != NULL)
					std::cout << "lower bound NOT NUL -----------------------" << std::endl;
				else
					std::cout << "lower bound is NUL -----------------------" << std::endl;
				if (locateBound(position.getPtr(), val.first, isUpperBoundNode) != NULL)
					std::cout << "upper bound NOT NUL -----------------------" << std::endl;
				else
					std::cout << "upper bound is NUL -----------------------" << std::endl;
				if (locateBound(position.getPtr(), val.first, isLowerBoundNode) != NULL)
					return (btree_insert_data(position.getPtr(), &(position.getPtr()->right), val).first);
				else
					return (btree_insert_data(NULL, &_head, val).first);
			}
			// 	if(position == NULL)
			// 		return (iterator());

			// 	ft::pair<iterator, bool> ret;
			// 	map_node*	posParent = position.getPosParent();
			// 	map_node*	posNode = position.getPtr();
			// 	if (posParent != NULL
			// 		&& (_comp(posParent->item.first, val.first) == true
			// 		|| _comp(val.first, posParent->item.first) == true))
			// 			ret = btree_insert_data(NULL, &_head, val);
			// 	else
			// 		ret = btree_insert_data(posNode, &posNode, val);
			// 	return (ret.first);
			// }

				/**
				 * @brief Range insert from first to last element
				*/
			template <class InputIterator>
 			void
			insert (InputIterator first, InputIterator last)	{

				for (; first != last; first++)
					insert(*first);
			}

			void
			erase( iterator position )	{

				map_node*	deadNode = position.getPtr();
				map_node*	deadNodeLeft = deadNode->left;
				map_node*	deadNodeRight = deadNode->right;
				map_node*	singleChild = getSingleChild(deadNode);

				if (deadNode == NULL)
					return;
				if (isLeaf(deadNode) == true)
					detachFromParent(deadNode);
				else if (singleChild != NULL)
					detachFromParent(deadNode, singleChild);
				else	{
					detachFromParent(deadNode, deadNodeLeft);
					map_node*	farRight = getFarRight(deadNodeLeft);
					deadNodeRight->parent = farRight;
					farRight->right = deadNodeRight;
				}
				decSize();
				btree_update_dumbNode();
				freeNode(deadNode);
			}

			size_type
			erase( const key_type& k )	{

				map_node*	target = btree_search_key(_head, k);
				if (target == NULL)
					return 0;
				else	{
					erase(iterator(target, _dumbNode, _comp));
					return (1);
				}
			}

			void
			erase (iterator first, iterator last)	{

				iterator next;
				while (first != last)	{
					next = first;
					next++;
					erase(first);
					first = next;
				}
			}

			void
			detachFromParent( map_node* node, map_node* newChild = NULL )	{
				map_node* parent = node->parent;
				if (parent != NULL)	{
					if (parent->left == node)
						parent->left = newChild;
					else if (parent->right == node)
						parent->right = newChild;
				}
				else if (node == _head)
					_head = newChild;
				if (newChild != NULL)
					newChild->parent = parent;
				node->parent = NULL;
			}

			static map_node*
			getSingleChild( map_node* node )	{

				if (node->right != NULL && node->left == NULL)
					return (node->right);
				else if (node->right == NULL && node->left != NULL)
					return (node->left);
				else
					return (NULL);
			}


			// size_type
			// erase (const key_type& k)	{

			// }

			// void
			// erase (iterator first, iterator last);	{

			// }


			void
			swap (map& src)	{

				if (this->_head != src._head)	{
					map_node*				tmp_head = src._head;
					map_node*				tmp_dumbNode = src._dumbNode;
					size_t					tmp_size = src._size;
					_node_allocator_type 	tmp_allocNode = src._allocNode;

					src._head = this->_head;
					src._dumbNode = this->_dumbNode;
					src._size = this->_size;
					src._allocNode = this->_allocNode;

					this->_head = tmp_head;
					this->_dumbNode = tmp_dumbNode;
					this->_size = tmp_size;
					this->_allocNode = tmp_allocNode;
				}
			}

// 			/**
// 			 * @brief Here we use the same technic as for insert : the type
// 			 *  integer is  used to call the right overload.
// 			*/
// 			template <class InputIterator>
// 			void assign (InputIterator first, InputIterator last)	{

// 				typename std::__is_integer<InputIterator>::__type	integer;
// 				assign_dispatch(first, last, integer);
// 			}

// 			void assign(size_type n, const mapped_type& val)	{

// 				clear();
// 				insert(begin(), n, val);
// 			}

// 			/**
// 			 * @brief Reserve: Requests that the map capacity be at
// 			 * least enough to contain n elements.
// 			*/
// 			void
// 			reserve (size_type n) {

// 				if (n > max_size())	{
// 					throw std::length_error("ft::map::reserve called with n > max_size");
// 				}
// 				else	{
// 					doReserve(n);
// 				}
// 			}

			map&
			operator= (const map& src)	{

				if (this->_head != src._head)	{
					clear();

					if (src.empty() == false)	{
						if (src.size() > 2)	{
							iterator	half = src.begin();
							for (size_t i = 0; i < src.size() / 2; i++)
								half++;
							insert(*half);
						}
						insert(src.begin(), src.end());
					}
				}
				return *this;
			}

			mapped_type&
			operator[]( const Key& key )	{

				// return (*((this->insert(make_pair(key,mapped_type()))).first).second);

				value_type					insertValue(key, mapped_type());
				ft::pair<iterator, bool>	ret = insert(insertValue);
				return (ret.first->second);
			}

            value_compare	value_comp() const	{ return value_compare(_comp); }
            key_compare		key_comp() const	{ return key_compare(_comp); }

// /******************************************************************************.
// .******************************************************************************.
// .*********** PRIVATE MEMBER FUNCTIONS AND HELPERS  ****************************.
// .******************************************************************************.
// .******************************************************************************/

 		private:

			map_node*
			locateBound( map_node* root, const key_type& key, bool (*predicate)(map_node*, const key_type&) ) const	{

				if (predicate(_dumbNode->left, key) == true)
					return (_dumbNode->left);
				else if (predicate(_dumbNode->right, key) == false)
					return (NULL);

				map_node* candidate = root;
				map_node* bestCandidate = NULL;
				while (candidate != NULL)	{
					if (predicate(candidate, key) == true)	{
						bestCandidate = candidate;
						candidate = candidate->left;
					}
					else
						candidate = candidate->right;
				}
				return (bestCandidate);
			}

			map_node*
			locateNode( map_node* root, const key_type& key ) const	{

				if (root != NULL)	{
					if (_comp(key, root->item.first) == true)
						return (locateNode(root->left, key));
					else if (isEqualKey(key, root->item.first) == false)
						return (locateNode(root->right, key));
					else
						return (root);
				}
				else
					return (NULL);
			}

			static bool
			isLowerBoundNode( map_node* node, const key_type& key ) {

			typename ft::map<Key, T, Compare> tmpObj;
			typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();

				return (node != NULL
					&& (cmpFunc(node->item.first, key) == false
						|| isEqualKey(node->item.first, key) == true));
			}

			static bool
			isUpperBoundNode( map_node* node, const key_type& key ) {
				typename ft::map<Key, T, Compare> tmpObj;
				typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();
				return (node != NULL && cmpFunc(key, node->item.first) == true);
			}

			void
			btree_update_dumbNode( map_node* node )	{
				if (_dumbNode == NULL)
					btree_init_dumbNode();
				if (node == getFarLeft(_head))
					_dumbNode->left = node;
				if (node == getFarRight(_head))
					_dumbNode->right = node;
			}

			void
			btree_update_dumbNode( void )	{
				if (_dumbNode == NULL)
					btree_init_dumbNode();
				_dumbNode->left = getFarLeft(_head);
				_dumbNode->right = getFarRight(_head);
			}

			void
			btree_init_dumbNode( void )	{

				if (_dumbNode == NULL)	{
					_dumbNode = _allocNode.allocate(1);
					_allocNode.construct(_dumbNode, map_node(value_type()));
				}
			}

			map_node*
			btree_create_node(map_node* parent, key_type k, mapped_type val)	{

				map_node*	newNode = _allocNode.allocate(1);
				_allocNode.construct(newNode, map_node(value_type(k ,val)));
				newNode->parent = parent;
				return (newNode);
			}

				/**
				 * @brief Actual function inserting new data in the tree.
				 * @param parent shall be NULL to insert anywhere from the head.
				 * @param root starting point in the tree to look for a suitable potision.
				 * @param pairSrc pair to be inserted.
				*/

			ft::pair<iterator, bool>
			btree_insert_data(map_node* parent, map_node **root, value_type pairSrc)	{

				if (*root != NULL)	{
					map_node* tree = *root;
					if (_comp(pairSrc.first, tree->item.first) == true)
						return (btree_insert_data(tree, &tree->left, pairSrc));
					else if (isEqualKey(pairSrc.first, tree->item.first) == false)
						return (btree_insert_data(tree, &tree->right, pairSrc));
					else
						return (ft::pair<iterator, bool>(iterator(*root, _dumbNode, _comp), false));
				}
				else	{
					*root = btree_create_node(parent, pairSrc.first, pairSrc.second);
					btree_update_dumbNode(*root);
					incSize();
					return (ft::pair<iterator, bool>(iterator(*root, _dumbNode, _comp), true));
				}
			}

			void
			btree_apply_item_prefix(map_node *root, void (*applyf)(value_type*))	{

				if (root == NULL)
					return;
				applyf(root->item);
				btree_apply_item_prefix(root->left, applyf);
				btree_apply_item_prefix(root->right, applyf);
			}


			void
			btree_apply_item_infix(map_node *root, void (*applyf)(value_type*))	{

				if (root == NULL)
					return;
				btree_apply_item_prefix(root->left, applyf);
				applyf(root->item);
				btree_apply_item_prefix(root->right, applyf);
			}

			void
			btree_apply_item_suffix(map_node *root, void (*applyf)(value_type*))	{

				if (root == NULL)
					return;
				btree_apply_item_prefix(root->left, applyf);
				btree_apply_item_prefix(root->right, applyf);
				applyf(root->item);
			}

			void
			btree_apply_node_prefix(map_node *root, void (*applyf)(map_node *))	{

				if (root == NULL)
					return;
				applyf(root);
				btree_apply_node_prefix(root->left, applyf);
				btree_apply_node_prefix(root->right, applyf);
			}

			void
			btree_apply_node_infix(map_node *root, void (*applyf)(map_node *))	{

				if (root == NULL)
					return;
				btree_apply_node_prefix(root->left, applyf);
				applyf(root);
				btree_apply_node_prefix(root->right, applyf);
			}

			void
			btree_apply_node_suffix(map_node *root, void (*applyf)(map_node *))	{

				if (root == NULL)
					return;
				btree_apply_node_prefix(root->left, applyf);
				btree_apply_node_prefix(root->right, applyf);
				applyf(root);
			}


			map_node*
			btree_search_key(map_node* root, const key_type& targetKey)	{

				if (root != NULL)	{
					if (_comp(targetKey, root->item.first) == true)
						return (btree_search_key(root->left, targetKey));
					else if (_comp(root->item.first, targetKey) == true)
						return (btree_search_key(root->right, targetKey));
				}
				return (root);
			}

			// size_t
			// tree_nodes_count(map_node *root)	{

			// }
			// void
			// btree_free_suffix(map_node *root)	{

			// }
			// size_t
			// tree_level_count(map_node *root)	{

			// }
			// void
			// btree_apply_by_level(map_node *root,
// 			void (*applyf)(void *item, int current_level, int is_first_elem))	{

// }

			static map_node*
			getFarLeft( map_node* cursor )  {

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			static map_node*
			getFarRight( map_node* cursor )  {

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}

			static bool
			isLeaf(map_node* node)  {
				return (node->left == NULL && node->right == NULL);
			}

			// bool
			// isRightEligible(pair_type& existingPair, pair_type& newPair)	{
			// 	return (comp(existingPair.first, newPair.first));
			// }

			// bool
			// isRightEligible(Key& existingKey, Key& newKey)	{
			// 	return (comp(existingKey, newKey));
			// }

			static bool
			isEqualKey(const Key& existingKey, const Key& newKey) {
				typename ft::map<Key, T, Compare> tmpObj;
				typename ft::map<Key, T, Compare>::key_compare cmpFunc = tmpObj.key_comp();
				return (cmpFunc(existingKey, newKey) == false
				&& cmpFunc(newKey, existingKey) == false);
			}


			size_t
			incSize( size_t inc = 1 ) { _size += inc; return(_size); }

			size_t
			decSize( size_t inc = 1 ) { _size -= inc; return(_size); }







// 			template <class InputIterator>
// 			void
// 			assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

// 				clear();
// 				insert(begin(), first, last);
// 			}

// 			template<typename integer>
// 			void
// 			assign_dispatch (integer n, integer val, std::__true_type)	{

// 				assign(static_cast<size_type>(n), static_cast<mapped_type>(val));
// 			}


// 			/**
// 			 * @brief Fill Constructor actual function
// 			*/
// 			template <class integer>
// 			void
// 			map_constructor_dispatch (integer n, integer const & val,
// 				allocator_type const &, std::__true_type)	{

// 				if (DEBUG_MODE >= 1)	{
// 					std::cout << "dispatch --> __true_type " << __func__ << std::endl;
// 					std::cout << "CONSTRUCTOR --> fill " << __func__ << std::endl;
// 				}
// 				this->initStorage(n);
// 				initFillmap(n, val);
// 			}

// 			/**
// 			 * @brief Range Constructor actual function
// 			*/
// 			template <class InputIterator>
// 			void
// 			map_constructor_dispatch (InputIterator first, InputIterator last,
// 				 allocator_type const &, std::__false_type)	{

// 				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range : " << __func__ << std::endl;

// 				size_t	n = std::distance(first, last);
// 				this->initStorage(n * 2);
// 				fillmap(first, last);
// 			}


// 			template<typename integer>
// 			void
// 			insert_dispatch(iterator position, integer n, integer val,
// 			std::__true_type)	{
// 				insert(position, static_cast<size_type>(n),
// 					static_cast<mapped_type>(val));
// 			}

// 			template<typename InputIterator>
// 			void
// 			insert_dispatch(iterator position, InputIterator first,
// 			InputIterator last, std::__false_type)	{

// 				if (capacity() == 0)	{
// 					this->initStorage(1);
// 					position = begin();
// 				}

// 				difference_type indexPos = position - begin();
// 				size_type		n = last - first;
// 				if (_size() + n >= capacity())	{
// 					doReserve(capacity() + n + (capacity()>>1));
// 				}

// 				if (begin() + indexPos != end())	{
// 					if (_size() > 1)	{
// 						memMoveRight(begin() + indexPos, end(), n);
// 					}
// 					destroyObjects(this->_head + indexPos, _size() - indexPos);
// 					this->tail += n;
// 					constructObjects(this->_head + indexPos, first, last);
// 				}
// 				else {
// 					constructObjects(this->_head + indexPos, first, last);
// 					this->tail += n;
// 				}
// 			}

// 			/**
// 			 * @brief Construct objects at alocated memory, to be used by
// 			 * constructors
// 			*/
// 			void
// 			fillmap(iterator first, iterator last)	{

// 				for (;first != last; first++)	{
// 					this->_alloc.construct(this->tail, *first);
// 					this->tail++;
// 					if (this->tail == this->tailStorage)
// 						std::cout << "RESIZE HERE" << std::endl;			// not fixed yet
// 				}
// 			}

// 			/**
// 			 * @brief Construct objects at alocated memory, to be used by
// 			 * constructors
// 			*/
// 			void
// 			initFillmap(size_type n, mapped_type const & val)	{

// 				this->tail = this->_head + n;
// 				for (size_t i = 0; i < n; i++){
// 					this->_alloc.construct(this->_head + i, val);
// 				}
// 			}



// 			/**
// 			 * @brief doReserve: No throw version of Reserve.
// 			*/
// 			void
// 			doReserve (size_type n) {

// 				if (n > this->capacity())	{
// 					pointer		oldHead = this->_head;
// 					size_type	oldSize = this->_size();
// 					size_type	oldCapacity = this->capacity();

// 					reallocateBigger(n);

// 					destroyObjects(oldHead, oldSize);
// 					this->_alloc.deallocate(oldHead, oldCapacity);
// 				}
// 			}

// 			void
// 			reallocateBigger(size_type n)	{

// 				if (n > this->capacity())	{

// 					iterator	oldHeadIt = begin();
// 					iterator	oldTailIt = end();

// 					this->initStorage(n);
// 					constructObjects(this->_head, oldHeadIt, oldTailIt);
// 					this->tail += oldTailIt - oldHeadIt;
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, size_t n, mapped_type val = mapped_type())	{
// 				for (size_t i = 0; i < n; i++)	{
// 					this->_alloc.construct(p + i, val);
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, iterator first, iterator last)	{
// 				for (size_t i = 0; first != last; i++, first++)	{
// 					this->_alloc.construct(p + i, *first);
// 				}
// 			}

			// void
			// destroyObjects(pointer p, size_t n)	{
				// for (size_t i = 0; i < n; i++)	{
					// this->_alloc.destroy(p + i);
				// }
			// }

			void
			freeNode( map_node* node)	{
				if (node != NULL)	{
					_allocNode.destroy(node);
					_allocNode.deallocate(node, 1);
				}
			}

			void
			freeAllNodes( map_node* root )	{

				if (root == NULL)
					return;
				freeAllNodes(root->left);
				freeAllNodes(root->right);
				// freeItem(root->item);
				freeNode(root);
			}

// 			/**
// 			 * @brief Move [first, last] range by n memory blocks to theLeft
// 			*/
// 			void
// 			memMoveLeft(iterator first, iterator last, size_t n)	{			// to be tested
// 				while (first != last)	{
// 					constructObjects(first._ptr - n, 1, *first);
// 					destroyObjects(first._ptr, 1);
// 					first++;
// 				}
// 			}


// 			/**
// 			 * @brief Move [first, last] range by n memory blocks to the right
// 			*/
// 			void
// 			memMoveRight(iterator first, iterator last, size_t n)	{
// 				while (last != first)	{
// 					last--;
// 					constructObjects(last._ptr + n, 1, *last);
// 					destroyObjects(last._ptr, 1);
// 				}
// 			}

// 			void
// 			checkRange(size_type n)	const {
// 				if (n > _size())	{
// 					throw std::out_of_range("Out of map's range");
// 				}
// 			}

		}; // -------------------------------------------------------- Class map



/******************************************************************************.
.******************************************************************************.
.*********** PUBLIC NON MEMBER FUNCTIONS     **********************************.
.******************************************************************************.
.******************************************************************************/





		template <class Key, class T, class Compare, class Alloc>
		void
		swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)	{

			x.swap(y);
		};

		// template <class T, class Alloc>
		// bool
		// operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	if (lhs._size() != rhs._size())
		// 		return false;
		// 	if (lhs.front() != rhs.front() || lhs.back() != rhs.back())
		// 		return false;
		// 	return (std::equal(lhs.begin(), lhs.end(), rhs.begin()));
		// };

		// template <class T, class Alloc>
		// bool
		// operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs == rhs)); };


		// template <class T, class Alloc>
		// bool
		// operator<  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));

		// };

		// template <class T, class Alloc>
		// bool
		// operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs > rhs)); };

		// template <class T, class Alloc>
		// bool
		// operator>  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));

		// };

		// template <class T, class Alloc>
		// bool
		// operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{ return(!(lhs < rhs)); };



} // -------------------------------------------------------------- ft namespace


#endif /* *****BVALETTE****** MAP_HPP */
