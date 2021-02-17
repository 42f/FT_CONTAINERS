/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_merge.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:42 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 09:52:43 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester.hpp"


int
test_vector_merge( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 and odd values in list 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize * 2; i++)	{
			if (i % 2 == 0)	{
				ftl0.push_back(i);
				stdl0.push_back(i);
			}
			else	{
				ftl1.push_back(i);
				stdl1.push_back(i);
			}
		}
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list into itself ]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl0, greater_than);
		stdl0.merge(stdl0, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, greater_than);
		stdl0.merge(stdl1, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "DESCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " DESCENDING even values in list 0 and odd values in list 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = testSize * 2; i > 0 ; i--)	{
			if (i % 2 == 0)	{
				ftl0.push_back(i);
				stdl0.push_back(i);
			}
			else	{
				ftl1.push_back(i);
				stdl1.push_back(i);
			}
		}

		ftl1.push_back(1000);
		stdl1.push_back(1000);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with smaller_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, smaller_than);
		stdl0.merge(stdl1, smaller_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 1000000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0 and list 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&stdl0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ftl0.push_back(val);
			stdl0.push_back(val);
			val = rand() % 40;
			ftl1.push_back(val);
			stdl1.push_back(val);
		}
		ftl0.push_back(42);
		stdl0.push_back(42);
		ftl0.push_back(42);
		stdl0.push_back(42);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, greater_than);
		stdl0.merge(stdl1, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER - with merge(1)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 1000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0 and list 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&stdl0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ftl0.push_back(val);
			stdl0.push_back(val);
			val = rand() % 40;
			ftl1.push_back(val);
			stdl1.push_back(val);
		}
		ftl0.push_back(42);
		stdl0.push_back(42);
		ftl0.push_back(42);
		stdl0.push_back(42);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with no compare argument (merge(1)) ]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1);
		stdl0.merge(stdl1);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	return (0);
}
