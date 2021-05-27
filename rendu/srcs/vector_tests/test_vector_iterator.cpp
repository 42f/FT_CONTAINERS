/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_iterator.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:38 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/27 18:03:54 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"

void
test_constIterator( ft::vector<int> const & ft_c0, std::vector<int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	ft::vector<int>::const_iterator		ft_it = ft_c0.begin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::vector<int>::const_iterator		ft_itend = (ft_c0.end() - 1); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::vector<int>::const_iterator	std_it = std_c0.begin();
	std::vector<int>::const_iterator	std_itend = (std_c0.end() - 1);

	testBool(*ft_it== *std_it, __LINE__);
	testBool(*ft_itend == *std_itend, __LINE__);
	ft_it++;
	std_it++;
	testBool(*ft_it== *std_it, __LINE__);
}

int
test_vector_iterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER VALUES" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Iterator construction: default ]" << RESET_COLOR << std::endl;
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

		ft::vector<int>		ft_c0;
		std::vector<int>	std_c0;
		int testSize = 42;

		for (int i = 0; i < testSize; i++)	{
			ft_c0.insert(ft_c0.end(), i);
			std_c0.insert(std_c0.end(), i);
		}
		testVector(ft_c0, std_c0, NOPRINT);

		ft::vector<int>::iterator ft_it0;
		std::vector<int>::iterator std_it0;

		std::cout << SUBTITLE << "[ Iterator construction: copy assignation ]" << RESET_COLOR << std::endl;
		ft_it0 = ft_c0.begin();
		std_it0	= std_c0.begin();

		std::cout << SUBTITLE << "[ Iterator construction: copye construction ]" << RESET_COLOR << std::endl;
		ft::vector<int>::iterator ft_it1(ft_it0);
		std::vector<int>::iterator std_it1(std_it0);

		std::cout << SUBTITLE << "[ Pre post increment decrement of iterator ]" << RESET_COLOR << std::endl;
		testBool(*ft_it0 == *std_it0, __LINE__);
		ft_it0++;
		std_it0++;
		testBool(*ft_it0 == *std_it0, __LINE__);
		ft_it0 += 21;
		std_it0 += 21;
		testBool(*ft_it0 == *std_it0, __LINE__);
		ft_it0--;
		std_it0--;
		testBool(*ft_it0 == *std_it0, __LINE__);
		std::cout << SUBTITLE << "[ operator[] ]" << RESET_COLOR << std::endl;
		testBool(ft_it0[4] == std_it0[4], __LINE__);
		testBool(ft_it0[-4] == std_it0[-4], __LINE__);
		std::cout << SUBTITLE << "[ Pre post increment decrement of value with * ]" << RESET_COLOR << std::endl;
		*ft_it0++;
		*std_it0++;
		testBool(*ft_it0 == *std_it0, __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);

		ft_it1 = ft_it0;
		std_it1 = std_it0;
		std::cout << SUBTITLE << "[ Relational Operators ]" << RESET_COLOR << std::endl;
		testBool(ft_it0 == ft_it1 && std_it0 == std_it1, __LINE__);
		testBool(ft_it0 >= ft_it1 && std_it0 >= std_it1, __LINE__);
		testBool(ft_it0 <= ft_it1 && std_it0 <= std_it1, __LINE__);
		ft_it1 = ft_c0.begin();
		std_it1 = std_c0.begin();
		testBool(ft_it0 != ft_it1 && std_it0 != std_it1, __LINE__);
		testBool(ft_it0 > ft_it1 && std_it0 > std_it1, __LINE__);
		testBool(ft_it0 >= ft_it1 && std_it0 >= std_it1, __LINE__);
		testBool(ft_it1 < ft_it0 && std_it1 < std_it0, __LINE__);
		testBool(ft_it1 <= ft_it0 && std_it1 <= std_it0, __LINE__);
		ft_it0 = ft_c0.begin();
		std_it0 = std_c0.begin();
		ft_it0 += 5;
		std_it0 += 5;
		std::cout << SUBTITLE << "[ iterator substraction ]" << RESET_COLOR << std::endl;
		testBool(ft_it0 - ft_it1 == std_it0 - std_it1, __LINE__);
		testBool(ft_it1 - ft_it0 == std_it1 - std_it0, __LINE__);

		std::cout << SUBTITLE << "[ iterator addition ]" << RESET_COLOR << std::endl;
		ft_it0 = ft_c0.begin() + 10;
		std_it0 = std_c0.begin() + 10;
		testBool(ft_it0 - ft_it1 == std_it0 - std_it1, __LINE__);
		testBool(ft_it1 - ft_it0 == std_it1 - std_it0, __LINE__);

		std::cout << SUBTITLE << "[ iterator's value changed but dereferencing with operator*]" << RESET_COLOR << std::endl;
		*ft_it0 = 5000;
		*std_it0 = 5000;
		testBool(*ft_it0 == *std_it0, __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ iterator's value changed but dereferencing with operator[] ]" << RESET_COLOR << std::endl;
		ft_it0[1] = 42;
		std_it0[1] = 42;
		testBool(*ft_it0 == *std_it0, __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << SUBTITLE << "[ iterator's value changed but dereferencing with operator->]" << RESET_COLOR << std::endl;

		ft::vector<std::pair<int, int> >				ft_c0(12, std::make_pair(1, 2));
		std::vector<std::pair<int, int> >				std_c0(12, std::make_pair(1, 2));
		ft::vector<std::pair<int, int> >::iterator 		ft_it0 = ft_c0.begin();
		std::vector<std::pair<int, int> >::iterator 	std_it0 = std_c0.begin();

		testBool(ft_it0->first == std_it0->first, __LINE__);
		testBool(ft_it0->second == std_it0->second, __LINE__);
	}

	return (0);
}
