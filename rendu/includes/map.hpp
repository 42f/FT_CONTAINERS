#ifndef MAP_HPP
# define MAP_HPP

# include "map_pair.hpp"
# include "map_iterator.hpp"

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


/*############################################################################*/
/*############################################################################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*###########################           btreeNode         ####################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*############################################################################*/
/*############################################################################*/



	template< typename Key, typename T>
	struct btreeNode	{

		typedef		Key							key_type;
		typedef		T							value_type;
		typedef		btreeNode *					base_pointer;
		typedef		typename ft::pair<Key, T>	pair_type;

		base_pointer		parent;
		base_pointer 		left;
		pair_type			pair;
		base_pointer 		right;

		base_pointer		getParent( void ) const	{ return this->parent;	}
		base_pointer		getLeft( void ) const	{ return this->left;	}
		base_pointer		getRight( void ) const	{ return this->right;	}
		pair_type&			getPair( void ) 		{ return this->pair;	}

		void			setParent(base_pointer parent)	{this->parent = parent; }
		void			setLeft(base_pointer newNode)	{this->left = newNode; 	}
		void			setRight(base_pointer newNode)	{this->right = newNode; }
		void			setPair(pair_type& newPair)		{this->pair = newPair; 	}

		btreeNode() : left(NULL), pair(key_type(), value_type()), right(NULL)	{}
		btreeNode(pair_type pairSrc) : left(NULL), pair(pairSrc), right(NULL)	{

			std::cout << __func__ << ": " << this << std::endl;
			std::cout << __func__ << ": " << getRight() << std::endl;
			std::cout << __func__ << ": " << getLeft() << std::endl;
		}
		~btreeNode() {}
	};		// btreeNode




/*############################################################################*/
/*############################################################################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*###########################           btree             ####################*/
/*###########################                             ####################*/
/*###########################                             ####################*/
/*############################################################################*/
/*############################################################################*/



	template< 	class Key,
				class T,
				class T_alloc,
				class Compare >
	class btree {

		public:

			typedef	typename ft::pair<Key, T>							pair_type;
			typedef	typename ft::btreeNode<Key, T>						node_type;
			typedef typename T_alloc::template rebind< btreeNode<Key, T> >::other	allocator_type;
			typedef Compare												key_compare;
			typedef typename T_alloc::reference							reference;
			typedef typename T_alloc::const_reference					const_reference;
			typedef typename T_alloc::pointer							pointer;
			typedef typename T_alloc::const_pointer						const_pointer;

			// btree( void ) : head(NULL), size(0), alloc(allocator_type()), cmp(key_compare()) {

			// 	if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
			// }

			explicit btree( const Compare &comp, allocator_type const & userAlloc ) : head(NULL), size(0), alloc(userAlloc), cmp(comp) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> defaut with alloc " << __func__ << std::endl;
			}

/*
			btree( btree const & src ) : head(NULL), size(0), alloc(allocator_type()) {

				(void)src;
				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;
			}

			btree( btree const & src, allocator_type const & userAlloc ) : head(src.head), size(src.size), alloc(userAlloc) {

				if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> copy with alloc " << __func__ << std::endl;
			}
*/
			~btree( void )	{

				deleteStorage();
				if (DEBUG_MODE >= 2) std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			pointer					head;
			size_t					size;
			allocator_type 			alloc;
			Compare	const			cmp;

		public:      // TEST PURPOSE: remove !

			pointer
			getFarLeft( pointer cursor )	{

				while (cursor != NULL && cursor->left != NULL)
					cursor = cursor->left;
				return (cursor);
			}

			pointer
			getFarRight( pointer cursor )	{

				while (cursor != NULL && cursor->right != NULL)
					cursor = cursor->right;
				return (cursor);
			}

			bool
			isLeaf(pointer node)	{
				return (node->getLeft() == NULL && node->getRight() == NULL);
			}

			bool
			isRightEligible(pair_type& existingPair, pair_type& newPair)	{
				return (cmp(existingPair.first, newPair.first));
			}

			bool
			isRightEligible(Key& existingKey, Key& newKey)	{
				return (cmp(existingKey, newKey));
			}

			bool
			isEqualKey(Key& existingKey, Key& newKey)	{
				return (cmp(existingKey, newKey) == false
				&& cmp(newKey, existingKey) == false);
			}

			pointer
			locateKeyPosition( Key& target )	{

				pointer	cursor = head;
				while ( cursor != NULL && isEqualKey(cursor->getPair().first, target) == false )	{
					if ( isRightEligible(cursor->getPair().first, target) == true)
						cursor = cursor->getRight();
					else
						cursor = cursor->getLeft();
				}
				return (cursor);
			}

			pointer
			makeNode(pair_type& newPair, pointer parent)	{

				pointer newNode = alloc.allocate(1);
				alloc.construct(newNode, newPair);
				if (DEBUG_MODE >= 2) std::cout << __func__ << "PARENT : " << parent << std::endl;
				newNode->setParent(parent);
				return (newNode);
			}

			void
			addNodeProcess( pointer parent, pointer* root, pair_type& srcPair )	{

				if (*root != NULL)	{
					pointer tree = *root;
					if (isRightEligible(tree->getPair(), srcPair) == true)	{
						addNodeProcess(tree, &(tree->right), srcPair);
					}
					else	{
						addNodeProcess(tree, &(tree->left), srcPair);
					}
				}
				else	{
					*root = makeNode(srcPair, parent);
					incSize();
				}
			}

			void
			addNode( pair_type& srcPair )	{
				addNodeProcess(NULL, &head, srcPair);
			}


		// protected:


			static void
			debugPrintNode( pointer node )	{

				if (DEBUG_MODE >= 2 && node != NULL)	{
					std::cout << std::endl;
					std::cout << __func__ << std::endl;
					std::cout << __func__ << ": node   " << node << std::endl;
					std::cout << __func__ << ": parent " << node->parent << std::endl;
					std::cout << __func__ << ": left   " << node->left << std::endl;
					std::cout << __func__ << ": right  " << node->right << std::endl;
					std::cout << __func__ << ": key    " << node->pair.first << std::endl;
					std::cout << __func__ << ": data   " << node->pair.second << std::endl;
					std::cout << std::endl;
				}
				else
					std::cout << __func__ << "Called with null" << std::endl;

			}

			void
			applyNodePrefix( pointer root, bool (*func)(pair_type&, pair_type& ))	{

				if (func == NULL || root == NULL)
					return ;
				func(root);
				applyNodePrefix(root->getLeft(), func);
				applyNodePrefix(root->getRight(), func);
			}

			void
			applyNodePrefix( pointer root, void (*func)(pointer))	{

				if (func == NULL || root == NULL)
					return ;
				func(root);
				applyNodePrefix(root->getLeft(), func);
				applyNodePrefix(root->getRight(), func);
			}

			void
			applyNodeSuffix( pointer root, void (*func)(pointer))	{

				if (func == NULL || root == NULL)
					return ;
				applyNodeSuffix(root->getLeft(), func);
				applyNodeSuffix(root->getRight(), func);
				func(root);
			}

			void
			applyNodeInfix( pointer root, void (*func)(pointer))	{

				if (func == NULL || root == NULL)
					return ;
				applyNodeInfix(root->getLeft(), func);
				func(root);
				applyNodeInfix(root->getRight(), func);
			}


			void
			debugPrintTree( void )	{

				debugPrintTreeProcess(*head);
			}

			void
			debugPrintTreeProcess( node_type& node )	{

				std::cout << "***********************************" << std::endl;
				std::cout << __func__ << "Printing tree of size  " << size << std::endl;
				applyNodePrefix(&node, debugPrintNode);
			}

			// void
			// initStorage( pair_type pairSrc )	{

			// 	//use makeNode ?
			// 	head = alloc.allocate(1);
			// 	alloc.construct(head, pairSrc);
			// 	incSize();
			// 	if (DEBUG_MODE >= 2)	{
			// 		std::cout << __func__ << std::endl;
			// 		// debugPrintNode(head);
			// 	}
			// }

		private:

			void
			incSize( void ) { size++; }

			void
			decSize( void ) { size--; }

			void
			deallocateTreeNodes( pointer root )	{

				if (root == NULL)
					return ;
				deallocateTreeNodes(root->getLeft());
				deallocateTreeNodes(root->getRight());
				this->alloc.deallocate(root, 1);
			}

			void
			deleteStorage( void )	{
				if (DEBUG_MODE >= 2) std::cout << __func__ << std::endl;
				deallocateTreeNodes(head);
			}

		}; // ----------------- Classbtree















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
				class T_alloc = std::allocator<btreeNode<Key, T> > >
	// class map : protected btree<Key, T, Compare, T_alloc> {
	class map : public btree<Key, T, T_alloc, Compare> {

		private:
			typedef btree<Key, T, T_alloc, Compare>		btree;
		public:
			typedef Key									key_type;
			typedef T									value_type;
			typedef	Compare								key_compare;
   			// typedef typename T_alloc::allocator_type		allocator_type;
   			typedef typename btree::allocator_type		allocator_type;

			typedef typename T_alloc::reference				reference;
			typedef typename T_alloc::const_reference		const_reference;
			typedef typename T_alloc::pointer				pointer;
			typedef typename T_alloc::const_pointer			const_pointer;
			typedef mapIterator<ft::pair<Key, T> >			iterator;
			// typedef const mapIterator<T>					const_iterator;
			// typedef std::reverse_iterator<iterator> 		reverse_iterator;
			// typedef const reverse_iterator				const_reverse_iterator;
			typedef std::ptrdiff_t							difference_type;
			typedef size_t									size_type;

/******************************************************************************.
.******************************************************************************.
.*********** CONSTRUCTORS DESTRUCTOR ******************************************.
.******************************************************************************.
.******************************************************************************/


		public:
			/**
			 * @brief Default Constructor
			*/
      		// explicit map() : btree() {

			// 	if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> DEFAULT " << __func__ << std::endl;

			//   }
			map( const Compare& comp = key_compare(), const allocator_type & userAlloc = allocator_type() ) : btree(comp, userAlloc) {

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> DEFAULT explicite " << __func__ << std::endl;
			}


			/**
			 * @brief Range Constructor
			*/
			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& userAlloc = allocator_type() )
				 : btree(comp, userAlloc)	{

				if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> range pre dispatcher ! " << __func__ << std::endl;

				typename std::__is_integer<InputIterator>::__type	integer;
				map_constructor_dispatch(first, last, userAlloc, integer);
			}

			// /**
			//  * @brief Copy Constructor
			// */
			// explicit map( map const & src ) : btree(src.size()) {

			// 	if (DEBUG_MODE >= 1) std::cout << "CONSTRUCTOR --> copy " << __func__ << std::endl;

			// 	fillmap(src.begin(), src.end());
			// }


			~map( void )	{

				// if (size() > 0)
				// 	clearObject();
				if (DEBUG_MODE >= 1)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

/******************************************************************************.
.******************************************************************************.
.*********** PUBLIC MEMBER FUNCTIONS ******************************************.
.******************************************************************************.
.******************************************************************************/

// 			size_type
// 			max_size( void ) const	{ return this->alloc.max_size();  }

// 			bool
// 			empty( void ) const		{ return (size() == 0); }

// 			size_type
// 			size( void ) const 		{ return (this->tail - this->head); }

			iterator
			begin( void ) 			{ return (this->getFarLeft(this->head)); }

// 			const_iterator
// 			begin( void ) const		{ return (this->head); }

			// iterator
			// end( void ) 	 		{ return (this->getFarRight(this->head)); }

// 			const_iterator
// 			end( void ) const 		{ return (this->tail); }

// 			reverse_iterator
// 			rbegin( void ) 			{ return reverse_iterator(end()); }

// 			const_reverse_iterator
// 			rbegin( void ) const	{ return reverse_iterator(end()); }

// 			reverse_iterator
// 			rend( void ) 	 		{ return reverse_iterator(begin()); }

// 			const_reverse_iterator
// 			rend( void ) const 		{ return reverse_iterator(begin()); }

// 			reference
// 			front( void ) 			{ return (*(this->head)); }

// 			const_reference
// 			front( void ) const		{ return (*(this->head)); }

// 			reference
// 			back( void ) 	 		{ return (*(this->tail - 1)); }

// 			const_reference
// 			back( void ) const 		{ return (*(this->tail - 1)); }

// 			size_type
// 			capacity( void ) const	{ return (this->tailStorage - this->head); }

// 			void
// 			pop_back( void )		{ if (size() > 0) erase(--end()); }

// 			void
// 			push_back (value_type const & val)	{ insert(end(), val); }

// 			void
// 			clear( void )			{ erase(begin(), end()); }

// 			/**
// 			 * @brief insert single element
// 			*/
// 			iterator insert(iterator position, const value_type& val)	{

// 				difference_type indexPos = position - begin();
// 				insert(position, 1, val);
// 				return begin() + indexPos; 		// to change
// 			}

// 			/**
// 			 * @brief insert n elements of val
// 			*/
// 			void insert (iterator position, size_type n, const value_type& val)	{

// 				if (capacity() == 0)	{
// 					this->initStorage(1);
// 					position = begin();
// 				}

// 				difference_type indexPos = position - begin();
// 				if (size() + n >= capacity())	{
// 					doReserve(capacity() + n + (capacity()>>1));
// 				}

// 				if (begin() + indexPos != end())	{
// 					if (size() > 1)	{
// 						memMoveRight(begin() + indexPos, end(), n);
// 					}
// 					destroyObjects(this->head + indexPos, size() - indexPos);
// 					this->tail += n;
// 					constructObjects(this->head + indexPos, n, val);
// 				}
// 				else {
// 					constructObjects(this->tail, n, val);
// 					this->tail += n;
// 				}
// 			}


// 			reference
// 			at (size_type n)	{
// 				checkRange(n);
// 				return ((*this)[n]);
// 			}

// 			const_reference
// 			at (size_type n) const	{
// 				checkRange(n);
// 				return ((*this)[n]);
// 			}

// 			/**
// 			 * @brief insert range of elements
// 			 * check here if arguments of type InputIterator are integer
// 			 * or iterators and dispatch to the right overload.
// 			 * Cf. /usr/include/c++/7/bits/cpp_type_traits.h line 136
// 			 * for implementation. Basicly __is_integer is a template function
// 			 * which, by default containts __false_type as __type, unless
// 			 * it is one of the integer types so it contains __true_type
// 			 * Here we create integer wich will be of type __true_type
// 			 * or __false_type, and by calling insert_dispatch with it, the right
// 			 * overload is called.
// 			*/
// 			template <class InputIterator>
// 			void
// 			insert (iterator position, InputIterator first,
// 			InputIterator last)	{

// 				typename std::__is_integer<InputIterator>::__type	integer;
// 				insert_dispatch(position, first, last, integer);
// 			}

// 			iterator
// 			erase (iterator position)	{

// 				destroyObjects(position._ptr, 1);
// 				memMoveLeft(position + 1, end(), 1);
// 				this->tail -= 1;
// 				return position;
// 			}

// 			iterator
// 			erase (iterator first, iterator last)	{

// 				size_type			offset = first - begin();
// 				difference_type		len = last - first;
// 				destroyObjects(first._ptr, len);
// 				memMoveLeft(last, end(), len);
// 				this->tail -= len;
// 				return begin() + offset;
// 			}

// 			void
// 			resize (size_type n, value_type val = value_type())	{

// 				if (n < size())	{
// 					erase(end() - (size() - n), end());
// 				}
// 				else if (n > size())	{
// 					insert(end(), n - size(), val);
// 				}
// 			}

// 			void
// 			swap (map& src)	{

// 				pointer 	headTmp = src.head;
// 				pointer 	tailTmp = src.tail;
// 				pointer		tailStorageTmp = src.tailStorage;

// 				src.head = this->head;
// 				src.tail = this->tail;
// 				src.tailStorage = this->tailStorage;

// 				this->head = headTmp;
// 				this->tail = tailTmp;
// 				this->tailStorage = tailStorageTmp;
// 			}

// 			/**
// 			 * @brief Here we use the same technic as for insert : the type
// 			 *  integer is  used to call the right overload.
// 			*/
// 			template <class InputIterator>
// 			void assign (InputIterator first, InputIterator last)	{

// 				typename std::__is_integer<InputIterator>::__type	integer;
// 				assign_dispatch(first, last, integer);
// 			}

// 			void assign(size_type n, const value_type& val)	{

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

// 			map&
// 			operator= (const map& x)	{

// 				if (*this != x)
// 					assign(x.begin(), x.end());
// 				return *this;
// 			}

			T&
			operator[]( const Key& key )	{

				pointer	cursor = btree::locateKeyPosition(key);
				if (cursor == NULL)
					std::cout <<  "NOT FOUND" << std::endl;
				else
					std::cout << "FOUND: " << cursor->getPair().first << " - " << cursor->getPair().second << std::endl;
				return (cursor->getPair().second);
			}

			// const_reference
			// operator[] (size_type n) const	{
			// 	return (*(this->head + n));
			// }

// /******************************************************************************.
// .******************************************************************************.
// .*********** PRIVATE MEMBER FUNCTIONS AND HELPERS  ****************************.
// .******************************************************************************.
// .******************************************************************************/

// 		private:

// 			template <class InputIterator>
// 			void
// 			assign_dispatch (InputIterator first, InputIterator last, std::__false_type)	{

// 				clear();
// 				insert(begin(), first, last);
// 			}

// 			template<typename integer>
// 			void
// 			assign_dispatch (integer n, integer val, std::__true_type)	{

// 				assign(static_cast<size_type>(n), static_cast<value_type>(val));
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
// 					static_cast<value_type>(val));
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
// 				if (size() + n >= capacity())	{
// 					doReserve(capacity() + n + (capacity()>>1));
// 				}

// 				if (begin() + indexPos != end())	{
// 					if (size() > 1)	{
// 						memMoveRight(begin() + indexPos, end(), n);
// 					}
// 					destroyObjects(this->head + indexPos, size() - indexPos);
// 					this->tail += n;
// 					constructObjects(this->head + indexPos, first, last);
// 				}
// 				else {
// 					constructObjects(this->head + indexPos, first, last);
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
// 					this->alloc.construct(this->tail, *first);
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
// 			initFillmap(size_type n, value_type const & val)	{

// 				this->tail = this->head + n;
// 				for (size_t i = 0; i < n; i++){
// 					this->alloc.construct(this->head + i, val);
// 				}
// 			}



// 			/**
// 			 * @brief doReserve: No throw version of Reserve.
// 			*/
// 			void
// 			doReserve (size_type n) {

// 				if (n > this->capacity())	{
// 					pointer		oldHead = this->head;
// 					size_type	oldSize = this->size();
// 					size_type	oldCapacity = this->capacity();

// 					reallocateBigger(n);

// 					destroyObjects(oldHead, oldSize);
// 					this->alloc.deallocate(oldHead, oldCapacity);
// 				}
// 			}

// 			void
// 			reallocateBigger(size_type n)	{

// 				if (n > this->capacity())	{

// 					iterator	oldHeadIt = begin();
// 					iterator	oldTailIt = end();

// 					this->initStorage(n);
// 					constructObjects(this->head, oldHeadIt, oldTailIt);
// 					this->tail += oldTailIt - oldHeadIt;
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, size_t n, value_type val = value_type())	{
// 				for (size_t i = 0; i < n; i++)	{
// 					this->alloc.construct(p + i, val);
// 				}
// 			}

// 			void
// 			constructObjects(pointer p, iterator first, iterator last)	{
// 				for (size_t i = 0; first != last; i++, first++)	{
// 					this->alloc.construct(p + i, *first);
// 				}
// 			}

// 			void
// 			destroyObjects(pointer p, size_t n)	{
// 				for (size_t i = 0; i < n; i++)	{
// 					this->alloc.destroy(p + i);
// 				}
// 			}

// 			void
// 			clearObject( void )	{

// 				if (DEBUG_MODE >= 3) std::cout << __func__ << std::endl;
// 				destroyObjects(this->head, this->size());
// 			}

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
// 				if (n > size())	{
// 					throw std::out_of_range("Out of map's range");
// 				}
// 			}
		}; // ----------------- Class map

		// template <class T, class Alloc >
		// void
		// swap (map<T,Alloc>& x, map<T,Alloc>& y)	{

		// 	x.swap(y);
		// };

		// template <class T, class Alloc>
		// bool
		// operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)	{

		// 	if (lhs.size() != rhs.size())
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
} // ----------------- ft namespace
#endif /* *****BVALETTE****** MAP_HPP */
