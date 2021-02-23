/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_iterator.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:38 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/23 09:01:38 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

void
test_constIterator( ft::vector<int> const & ft_c0, std::vector<int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	ft::vector<int>::const_iterator		ft_it = ft_c0.begin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::vector<int>::const_iterator		ft_itend = (ft_c0.end() - 1); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::vector<int>::const_iterator	std_it = std_c0.begin();
	std::vector<int>::const_iterator	std_itend = (std_c0.end() - 1);

	std::cout << "Test ft : operaotr * on const -> " << *ft_it << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_it << std::endl;
	std::cout << "Test ft : operaotr * on const -> " << *ft_itend << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_itend << std::endl;
	testBool(true);
}

int
test_vector_iterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER VALUES" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>	std_c0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in vector 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 1; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
		}
		ft::vector<int>::iterator		ft_it = ft_c0.begin();
		ft::vector<int>::iterator		ft_it2 = ft_c0.begin();
		ft::vector<int>::iterator		ft_itend = ft_c0.end();

		std::cout << SUBTITLE << "[ test operator< with iterator to begin < end ]" << RESET_COLOR << std::endl;
		testBool(ft_it < ft_itend, __LINE__);
		std::cout << SUBTITLE << "[ loop test iterator increment vs. iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < ft_c0.size(); i++)
		{
			testBool((*ft_it == *(ft_it2 + i)), __LINE__);
			ft_it++;
		}
		std::cout << SUBTITLE << "[ test operator= ]" << RESET_COLOR << std::endl;
		ft_it2 = ft_it;
		testBool(ft_it == ft_it2, __LINE__);
		std::cout << SUBTITLE << "[ loop test iterator increment vs. iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < ft_c0.size(); i++)
		{
			testBool((*ft_it == *(ft_it2 - i)), __LINE__);
			ft_it--;
		}
		testBool(static_cast<size_t>(ft_itend - ft_it) == ft_c0.size(), __LINE__);
		test_constIterator(ft_c0, std_c0);
	}
	std::cout << HEADER_TITLE << "TEST ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::vector<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::vector<int>::iterator it1 = ++l.begin();
		ft::vector<int>::iterator it2 = l.begin() + 2;
		it1++;
		ft::vector<int>::iterator ite1 = --l.end();
		ite1--;
		ft::vector<int>::iterator ite2 = l.end() - 2;

		testBool(*it1 == 2, __LINE__);
		testBool(*ite1 == 4, __LINE__);
		testBool(*(it1++) == 2, __LINE__);
		testBool(*(ite1++) == 4, __LINE__);
		it1--;
		ite1--;
		testBool(*it1 == *it2, __LINE__);
		testBool(*ite1 == *ite2, __LINE__);

	}

	return (0);
}
