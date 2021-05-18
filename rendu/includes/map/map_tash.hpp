


// /*############################################################################*/
// /*############################################################################*/
// /*###########################                             ####################*/
// /*###########################                             ####################*/
// /*###########################           btreeNode         ####################*/
// /*###########################                             ####################*/
// /*###########################                             ####################*/
// /*############################################################################*/
// /*############################################################################*/



	template< typename Key, typename T>
	struct btreeNode	{

		typedef		Key							key_type;
		typedef		T							mapped_type;
		typedef		btreeNode *					base_pointer;
		typedef		typename ft::pair<Key, T>	pair_type;

		// base_pointer		parent;
		base_pointer 		left;
		pair_type			pair;
		base_pointer 		right;

		// base_pointer		getParent( void ) const	{ return this->parent;	}
		// base_pointer		getLeft( void ) const	{ return this->left;	}
		// base_pointer		getRight( void ) const	{ return this->right;	}
		// pair_type&		getPair( void ) 		{ return this->pair;	}

		// void			setParent(base_pointer parent)	{this->parent = parent; }
		// void			setLeft(base_pointer newNode)	{this->left = newNode; 	}
		// void			setRight(base_pointer newNode)	{this->right = newNode; }
		// void			setPair(pair_type& newPair)		{this->pair = newPair; 	}

		btreeNode() : left(NULL), pair(key_type(), mapped_type()), right(NULL)	{}
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
				class Allocator,
				class Compare >
	class btree {

		public:

			typedef	typename ft::pair<Key, T>							pair_type;
			typedef	typename ft::btreeNode<Key, T>						node_type;
			typedef typename Allocator::template rebind< btreeNode<Key, T> >::other	allocator_type;
			typedef Compare												key_compare;
			typedef typename Allocator::reference							reference;
			typedef typename Allocator::const_reference					const_reference;
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer						const_pointer;

			// btree( void ) : head(NULL), size(0), alloc(allocator_type()), comp(key_compare()) {

			// 	if (DEBUG_MODE >= 2) std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;
			// }

			explicit btree( const Compare &comp, allocator_type const & userAlloc ) : head(NULL), size(0), alloc(userAlloc), comp(comp) {

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
			Compare	const			comp;

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
				return (comp(existingPair.first, newPair.first));
			}

			bool
			isRightEligible(Key& existingKey, Key& newKey)	{
				return (comp(existingKey, newKey));
			}

			bool
			isEqualKey(Key& existingKey, Key& newKey)	{
				return (comp(existingKey, newKey) == false
				&& comp(newKey, existingKey) == false);
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













