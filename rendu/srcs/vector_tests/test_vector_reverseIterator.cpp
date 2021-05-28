/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/28 09:42:30 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"

void
test_constReverseIterator( ft::vector<int> const & ft_c0, std::vector<int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse reverse_iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	ft::vector<int>::const_reverse_iterator		ft_it = ft_c0.rbegin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::vector<int>::const_reverse_iterator		ft_itend = (ft_c0.rend() - 1); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::vector<int>::const_reverse_iterator	std_it = std_c0.rbegin();
	std::vector<int>::const_reverse_iterator	std_itend = (std_c0.rend() - 1);

	testBool(*ft_it== *std_it, __LINE__);
	testBool(*ft_itend == *std_itend, __LINE__);
	ft_it++;
	std_it++;
	testBool(*ft_it== *std_it, __LINE__);
}

int
test_vector_reverseIterator( void )	{
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
		ft::vector<int>::reverse_iterator		ft_it = ft_c0.rbegin();
		ft::vector<int>::reverse_iterator		ft_it2 = ft_c0.rbegin();
		ft::vector<int>::reverse_iterator		ft_itend = ft_c0.rend();
		std::vector<int>::reverse_iterator		std_it = std_c0.rbegin();
		std::vector<int>::reverse_iterator		std_it2 = std_c0.rbegin();
		// std::vector<int>::reverse_iterator		std_itend = std_c0.rend();

		std::cout << SUBTITLE << "[ size of int ]" << sizeof(int) << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ test operator< with reverse_iterator to rbegin < rend ]" << RESET_COLOR << std::endl;
		testBool(ft_it > ft_itend, __LINE__);
		putVector(ft_c0);
		std::cout << SUBTITLE << "[ loop test reverse_iterator increment vs. reverse_iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i <= ft_c0.size(); i++)
		{
			testBool(*ft_it == *(ft_it2 + i) && *std_it == *(std_it2 + i), __LINE__, i);
			++ft_it;
			++std_it;
		}
		std::cout << SUBTITLE << "[ test operator= ]" << RESET_COLOR << std::endl;
		ft_it2 = ft_it;
		testBool(ft_it == ft_it2, __LINE__);
		std::cout << SUBTITLE << "[ loop test reverse_iterator increment vs. reverse_iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < ft_c0.size(); i++)
		{
			testBool((*ft_it == *(ft_it2 - i)), __LINE__);
			ft_it--;
		}
		testBool(static_cast<size_t>(ft_itend - ft_it) == ft_c0.size(), __LINE__);
		test_constReverseIterator(ft_c0, std_c0);
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

		ft::vector<int>::reverse_iterator ft_it0;
		std::vector<int>::reverse_iterator std_it0;

		std::cout << SUBTITLE << "[ Iterator construction: copy assignation ]" << RESET_COLOR << std::endl;
		ft_it0 = ft_c0.rbegin();
		std_it0	= std_c0.rbegin();

		std::cout << SUBTITLE << "[ Iterator construction: copye construction ]" << RESET_COLOR << std::endl;
		ft::vector<int>::reverse_iterator ft_it1(ft_it0);
		std::vector<int>::reverse_iterator std_it1(std_it0);

		std::cout << SUBTITLE << "[ Pre post increment decrement of reverse_iterator ]" << RESET_COLOR << std::endl;
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
		ft_it1 = ft_c0.rbegin();
		std_it1 = std_c0.rbegin();
		testBool(ft_it0 != ft_it1 && std_it0 != std_it1, __LINE__);
		testBool(ft_it0 > ft_it1 && std_it0 > std_it1, __LINE__);
		testBool(ft_it0 >= ft_it1 && std_it0 >= std_it1, __LINE__);
		testBool(ft_it1 < ft_it0 && std_it1 < std_it0, __LINE__);
		testBool(ft_it1 <= ft_it0 && std_it1 <= std_it0, __LINE__);
		ft_it0 = ft_c0.rbegin();
		std_it0 = std_c0.rbegin();
		ft_it0 += 5;
		std_it0 += 5;
		std::cout << SUBTITLE << "[ reverse_iterator substraction ]" << RESET_COLOR << std::endl;
		testBool(ft_it0 - ft_it1 == std_it0 - std_it1, __LINE__);
		testBool(ft_it1 - ft_it0 == std_it1 - std_it0, __LINE__);

		std::cout << SUBTITLE << "[ reverse_iterator addition ]" << RESET_COLOR << std::endl;
		ft_it0 = ft_c0.rbegin() + 10;
		std_it0 = std_c0.rbegin() + 10;
		testBool(ft_it0 - ft_it1 == std_it0 - std_it1, __LINE__);
		testBool(ft_it1 - ft_it0 == std_it1 - std_it0, __LINE__);

		std::cout << SUBTITLE << "[ reverse_iterator's value changed but dereferencing with operator*]" << RESET_COLOR << std::endl;
		*ft_it0 = 5000;
		*std_it0 = 5000;
		testBool(*ft_it0 == *std_it0, __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ reverse_iterator's value changed but dereferencing with operator[] ]" << RESET_COLOR << std::endl;
		ft_it0[1] = 42;
		std_it0[1] = 42;
		testBool(*ft_it0 == *std_it0, __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << SUBTITLE << "[ reverse_iterator's value changed but dereferencing with operator->]" << RESET_COLOR << std::endl;

		ft::vector<std::pair<int, int> >				ft_c0(12, std::make_pair(1, 2));
		std::vector<std::pair<int, int> >				std_c0(12, std::make_pair(1, 2));
		ft::vector<std::pair<int, int> >::reverse_iterator 		ft_it0 = ft_c0.rbegin();
		std::vector<std::pair<int, int> >::reverse_iterator 	std_it0 = std_c0.rbegin();

		testBool(ft_it0->first == std_it0->first, __LINE__);
		testBool(ft_it0->second == std_it0->second, __LINE__);
	}
	return (0);

}


// void
// test_constReverseIterator( ft::vector<int> const & ft_c0, std::vector<int> const & std_c0 )	{

// 	std::cout << HEADER_TITLE << "Test const version of reverse reverse_iterator" << RESET_COLOR << std::endl;
// 	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
// 	ft::vector<int>::const_reverse_iterator		ft_it = ft_c0.rbegin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
// 	ft::vector<int>::const_reverse_iterator		ft_itend = ft_c0.rend() - 1; //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

// 	std::vector<int>::const_reverse_iterator	std_it = std_c0.rbegin();
// 	std::vector<int>::const_reverse_iterator	std_itend = std_c0.rend() - 1;

// 	std::cout << "Test ft : operaotr * on const -> " << *ft_it << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
// 	std::cout << "Test std: operaotr * on const -> " << *std_it << std::endl;
// 	std::cout << "Test ft : operaotr * on const -> " << *ft_itend << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
// 	std::cout << "Test std: operaotr * on const -> " << *std_itend << std::endl;
// 	testBool(true);
// }

// int
// test_vector_reverseIterator( void )	{
// 	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
// 	{
// 	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
// 		ft::vector<int>		ft_c0;
// 		std::vector<int>	std_c0;
// 		size_t				testSize = 10;

// 		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in vector 0 ]" << RESET_COLOR << std::endl;

// 		for (size_t i = 1; i < testSize; i++)	{
// 			ft_c0.push_back(i);
// 			std_c0.push_back(i);
// 		}
// 		testVector(ft_c0, std_c0, NOPRINT);

// 		ft::vector<int>::reverse_iterator		ft_it = ft_c0.rbegin();
// 		ft::vector<int>::reverse_iterator		ft_it2 = ft_c0.rbegin();
// 		ft::vector<int>::reverse_iterator		ft_itend = ft_c0.rend();

// 		std::vector<int>::reverse_iterator		std_it = std_c0.rbegin();
// 		std::vector<int>::reverse_iterator		std_it2 = std_c0.rbegin();
// 		std::vector<int>::reverse_iterator		std_itend = std_c0.rend();

// 		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
// 		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
// 		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
// 		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
// 		test_constReverseIterator(ft_c0, std_c0);
// 	}
// 	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
// 	{
// 		// std::vector<int>			s;
// 		// s.reserve(20);
// 		// s.push_back(42);
// 		// s.push_back(1);
// 		// s.push_back(2);
// 		// s.push_back(3);
// 		// s.push_back(4);
// 		// s.push_back(5);
// 		// std::vector<int>::reverse_iterator s_rit = s.rbegin();
// 		// std::vector<int>::reverse_iterator s_rite = s.rend();
// 		// std::cout << "BASE rev rbegin : " <<	*(s.rbegin()) << std::endl;
// 		// std::cout << "BASE rev rend   : " <<	*(s.rend())	 << std::endl;
// 		// std::cout << "BASE rev rbegin  : " <<	*s_rit	 << std::endl;
// 		// std::cout << "BASE rev rend    : " <<	*s_rite	 << std::endl;
// 		// s_rit++;
// 		// s_rit++;
// 		// s_rite--;
// 		// s_rite--;

// 		// std::cout << "BASE rev rbegin ++ : " <<	*s_rit	 << std::endl;
// 		// std::cout << "BASE rev rend --   : " <<	*s_rite	 << std::endl;
// 		// std::cout << "BASE rev rbegin ++ base : " <<	*(s_rit.base())	 << std::endl;
// 		// std::cout << "BASE rev rend -- base   : " <<	*(s_rite.base())	 << std::endl;


// 		// exit(1);

// 		// ft::vector<int>			l;
// 		// l.push_back(0);
// 		// l.push_back(1);
// 		// l.push_back(2);
// 		// l.push_back(3);
// 		// l.push_back(4);
// 		// l.push_back(5);
// 		// ft::vector<int>::reverse_iterator l_rit = l.rbegin();
// 		// l_rit++;
// 		// l_rit++;
// 		// ft::vector<int>::reverse_iterator l_rite = l.rend();
// 		// l_rite--;
// 		// l_rite--;

// 		// testBool(*(l_rit.base()) == *(s_rit.base()), __LINE__);
// 		// testBool(*(l_rite.base()) == *(s_rite.base()), __LINE__);
// 		// testBool(*l_rite == *s_rite, __LINE__);
// 		// testBool(*l_rit == *s_rit, __LINE__);
// 	}
// 	return (0);
// }
