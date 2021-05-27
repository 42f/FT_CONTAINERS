/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_iterator.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:01:30 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/27 16:56:26 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_list.hpp"

int
test_list_iterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER VALUES" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			ftl0.push_back(i);
		}
		ft::list<int>::iterator		ft_it = ftl0.begin();
		ft::list<int>::iterator		ft_it2 = ftl0.begin();
		ft::list<int>::iterator		ft_itend = ftl0.end();

		std::cout << SUBTITLE << "[ test operator= ]" << RESET_COLOR << std::endl;
		ft_it2 = ft_it;
		testBool(ft_it == ft_it2, __LINE__);
	}
	std::cout << HEADER_TITLE << "TEST ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::list<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::list<int>::iterator it1 = ++l.begin();
		ft::list<int>::iterator it2 = ++l.begin();
		it2++;
		it1++;
		ft::list<int>::iterator ite1 = --l.end();
		ite1--;
		ft::list<int>::iterator ite2 = --l.end();
		ite2--;
		testBool(*it1 == 2, __LINE__);
		testBool(*ite1 == 4, __LINE__);
		testBool(*it1 == *it2, __LINE__);
		testBool(*ite1 == *ite2, __LINE__);
	}

	return (0);
}
