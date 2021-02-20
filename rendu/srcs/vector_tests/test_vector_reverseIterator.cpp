/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
		ft::vector<int>		ft_c0;
		std::vector<int>		std_c0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in vector 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
		}
		testVector(ft_c0, std_c0, NOPRINT);

		ft::vector<int>::reverse_iterator		ft_it = ft_c0.rbegin();
		ft::vector<int>::reverse_iterator		ft_it2 = ft_c0.rbegin();
		ft::vector<int>::reverse_iterator		ft_itend = ft_c0.rend();

		std::vector<int>::reverse_iterator		std_it = std_c0.rbegin();
		std::vector<int>::reverse_iterator		std_it2 = std_c0.rbegin();
		std::vector<int>::reverse_iterator		std_itend = std_c0.rend();

		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
	}
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::vector<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::vector<int>::reverse_iterator it1 = l.rbegin();
		ft::vector<int>::reverse_iterator it2 = l.rbegin();
		it1++;
		it1++;
		it2++;
		it2++;
		ft::vector<int>::reverse_iterator ite1 = l.rend();
		ft::vector<int>::reverse_iterator ite2 = l.rend();
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