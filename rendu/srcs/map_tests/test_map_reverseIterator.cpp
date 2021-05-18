/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/23 09:02:27 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

void
test_constReverseIterator( ft::map<int> const & ft_c0, std::map<int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	ft::map<int>::const_reverse_iterator		ft_it = ft_c0.rbegin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::map<int>::const_reverse_iterator		ft_itend = ft_c0.rend() - 1; //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::map<int>::const_reverse_iterator	std_it = std_c0.rbegin();
	std::map<int>::const_reverse_iterator	std_itend = std_c0.rend() - 1;

	std::cout << "Test ft : operaotr * on const -> " << *ft_it << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_it << std::endl;
	std::cout << "Test ft : operaotr * on const -> " << *ft_itend << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_itend << std::endl;
	testBool(true);
}

int
test_map_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
		ft::map<int>		ft_c0;
		std::map<int>	std_c0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in map 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 1; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
		}
		testMap(ft_c0, std_c0, NOPRINT);

		ft::map<int>::reverse_iterator		ft_it = ft_c0.rbegin();
		ft::map<int>::reverse_iterator		ft_it2 = ft_c0.rbegin();
		ft::map<int>::reverse_iterator		ft_itend = ft_c0.rend();

		std::map<int>::reverse_iterator		std_it = std_c0.rbegin();
		std::map<int>::reverse_iterator		std_it2 = std_c0.rbegin();
		std::map<int>::reverse_iterator		std_itend = std_c0.rend();

		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
		test_constReverseIterator(ft_c0, std_c0);
	}
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::map<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::map<int>::reverse_iterator it1 = l.rbegin();
		ft::map<int>::reverse_iterator it2 = l.rbegin();
		it1++;
		it1++;
		it2++;
		it2++;
		ft::map<int>::reverse_iterator ite1 = l.rend();
		ft::map<int>::reverse_iterator ite2 = l.rend();
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
