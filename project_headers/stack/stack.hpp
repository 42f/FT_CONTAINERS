/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 08:28:25 by bvalette          #+#    #+#             */
/*   Updated: 2021/07/07 08:56:50 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

#ifndef DEBUG_MODE
# define DEBUG_MODE 0
#endif

#include "../deque/deque.hpp"

namespace ft	{

	template <class T, class Container = ft::deque<T> >
	class stack 	{

/******************************************************************************.
.******************************************************************************.
.*********** MEMBER TYPES            ******************************************.
.******************************************************************************.
.******************************************************************************/

		public:

			typedef	T									value_type;
			typedef	Container							container_type;
			typedef	typename container_type::size_type	size_type;

			explicit
			stack (const container_type& ctnr = container_type()) : c(ctnr) {}

			bool
			empty( void )	const	{
				return c.empty();
			}

			size_type
			size( void )	const	{
				return c.size();
			}

			value_type&
			top()	{
				return (c.back());
			}

			const value_type&
			top() const	{
				return (c.back());
			}

			void
			push (const value_type& val)	{
				c.push_back(val);
			}

			void
			pop ( void )	{
				c.pop_back();
			}

			template <class Type, class _Cntnr>
			friend
			bool
			operator==(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			template <class Type, class _Cntnr>
			friend
			bool
			operator!=(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			template <class Type, class _Cntnr>
			friend
			bool
			operator<(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			template <class Type, class _Cntnr>
			friend
			bool
			operator<=(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			template <class Type, class _Cntnr>
			friend
			bool
			operator>(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			template <class Type, class _Cntnr>
			friend
			bool
			operator>=(const stack<Type, _Cntnr>& lhs, const stack<Type, _Cntnr>& rhs);

			Container	c;

	}; //------------------stack class

	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c != rhs.c;
	}

	template <class T, class Container>
	bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c <= rhs.c;
	}

	template <class T, class Container>
	bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c > rhs.c;
	}

	template <class T, class Container>
	bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)	{
		return lhs.c >= rhs.c;
	}

} //-----------------namespace ft

#endif
