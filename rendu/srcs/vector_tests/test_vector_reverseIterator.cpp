/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 10:43:06 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			ftl0.push_back(i);
			stdl0.push_back(i);
		}
		testList(ftl0, stdl0, NOPRINT);

		ft::list<int>::reverse_iterator		ft_it = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_it2 = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_itend = ftl0.rend();

		std::list<int>::reverse_iterator		std_it = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_it2 = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_itend = stdl0.rend();

		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
	}
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::list<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::list<int>::reverse_iterator it1 = l.rbegin();
		ft::list<int>::reverse_iterator it2 = l.rbegin();
		it1++;
		it1++;
		it2++;
		it2++;
		ft::list<int>::reverse_iterator ite1 = l.rend();
		ft::list<int>::reverse_iterator ite2 = l.rend();
		ite1--;
		ite1--;
		ite2--;
		ite2--;

		testBool(*it1 == 3, __LINE__);
		testBool(*ite1 == 1, __LINE__);
		testBool(*it1 == *it2, __LINE__);
		testBool(*ite1 == *ite2, __LINE__);
	}
	return (0);
}
