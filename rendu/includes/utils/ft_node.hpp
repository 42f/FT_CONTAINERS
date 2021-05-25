#ifndef FT_NODE_HPP
# define FT_NODE_HPP

# include <iostream>

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif


namespace ft	{

	template< typename T>
	class node	{

		public:
			node<T>	*next;
			node<T>	*prev;
			T		data;

			node( void ) : next(this), prev(this) {

				if (DEBUG_MODE >= 2)
					std::cout << "CONSTRUCTOR --> default " << __func__ << std::endl;

			}
			node( T const & val ) : next(this), prev(this), data(val) {

				if (DEBUG_MODE >= 3)
				{
					std::cout << "CONSTRUCTOR with Param--> " << __func__ << std::endl;
					std::cout << __func__ << " this: " << this << std::endl;
					std::cout << __func__ << " prev: " << prev << std::endl;
					std::cout << __func__ << " next: " << next << std::endl;
				}
			}

			~node( void )	{
				if (DEBUG_MODE >= 2)
					std::cout << "DESTRUCTOR --> " << __func__ << std::endl;
			}

			static void
			swap(node& x, node& y)	{

				if (&x != &y)	{
					node *posx;
					if (&y != x.next)
						posx = x.next;
					else
						posx = &x;
					node	*posy = y.next;
					y.unhook();
					y.hook(posx);
					x.unhook();
					x.hook(posy);
				}
			}

			void
			transfer(node * const first, node * const last)	{

				if (first != last)	{
					node *	beforeLast = last->prev;
					if (first->prev != first)	{
						first->prev->next = last;
						last->prev = first->prev;
						first->prev = first;
					}
					else
						last->prev = last;
					beforeLast->next = beforeLast;
				}
				if (DEBUG_MODE >= 3)
					putNodeInfos(*this);
			}

			void
			hook(node * const position)	{

				if (position != NULL)	{

					if (position->prev != position)
					{
						this->prev = position->prev;
						this->prev->next = this;
					}
					if (this->next == this)
					{
						this->next = position;
						position->prev = this;
					}
					else	{
						node * cursor = this;
						while (cursor->next != cursor)
							cursor = cursor->next;
						cursor->next = position;
						position->prev = cursor;
					}

					if (DEBUG_MODE >= 3)
					{
						std::cout << __func__ << " at position: " << position << std::endl;
						std::cout << __func__ << " prev = " << prev << std::endl;
						std::cout << __func__ << " next = " << next << std::endl;
						putNodeInfos(*this);
					}
				}
			}

			void
			unhook( void )	{

			if (DEBUG_MODE >= 3)
				putNodeInfos(*this);

				if (prev != this && next != this)	{
					next->prev = prev;
					prev->next = next;
				}
				else if (prev == this)
					next->prev = next;
				else if (next == this)
					prev->next = prev;
				this->next = this;
				this->prev = this;
			if (DEBUG_MODE >= 3)
				putNodeInfos(*this);
			}

			static void	putNodeInfos(node<T> const &n) {
				std::cout << std::endl;
				std::cout << "--NODE: " << &n << std::endl;
				std::cout << "data -> " << n.data << " @ " << &(n.data) << std::endl;
				std::cout << "prev -> " << n.prev << std::endl;
				std::cout << "next -> " << n.next << std::endl;
				// if (n != _tail && n.next != &(n))
				// 	putNodeInfos(*n.next);
				// else
					std::cout << std::endl;
			}
		}; // ----------------- Class node

} // ----------------- ft namespace

#endif
