/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 08:28:25 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/07 22:05:55 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

#include "../deque/deque.hpp"
// #include "../vector/vector_iterator.hpp"

namespace ft	{

	template <class T, class Container = ft::deque<T> >
	class stack 	{

/******************************************************************************.
.******************************************************************************.
.*********** MEMBER TYPES            ******************************************.
.******************************************************************************.
.******************************************************************************/
		friend class stack<T, Container>;
		public:

			typedef	T									value_type;
			typedef	Container							container_type;
			typedef	typename container_type::size_type	size_type;

			explicit
			stack (const container_type& ctnr = container_type()) : _container(ctnr) {}

			bool
			empty( void )	const	{
				return _container.empty();
			}

			size_type
			size( void )	const	{
				return _container.size();
			}

			value_type&
			top()	{
				return (_container.back());
			}

			const value_type&
			top() const	{
				return (_container.back());
			}

			void
			push (const value_type& val)	{
				_container.push(val);
			}

			void
			pop ( void )	{
				_container.pop_back();
			}

			// bool
			// operator==(const stack <T, Container>& rhs)	{
			// 	if (size() != rhs.size())
			// 		return false;
			// 	else
			// 		return true;
			// }

		private:

			Container	_container;

	}; //------------------stack class

	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator==(lhs, rhs);
	}

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator!=(lhs, rhs);
	}

	template <class T, class Container>
	bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator<(lhs, rhs);
	}

	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator<=(lhs, rhs);
	}

	template <class T, class Container>
	bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator>(lhs, rhs);
	}

	template <class T, class Container>
	bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return Container().operator>=(lhs, rhs);
	}

} //-----------------namespace ft

#endif
