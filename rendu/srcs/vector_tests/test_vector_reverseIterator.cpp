/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_reverseIterator.cpp                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:28 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/25 12:07:02 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"

void
test_constReverseIterator( ft::vector<int> const & ft_c0, std::vector<int> const & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;
	ft::vector<int>::const_reverse_iterator		ft_it = ft_c0.rbegin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::vector<int>::const_reverse_iterator		ft_itend = ft_c0.rend() - 1; //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::vector<int>::const_reverse_iterator	std_it = std_c0.rbegin();
	std::vector<int>::const_reverse_iterator	std_itend = std_c0.rend() - 1;

	std::cout << "Test ft : operaotr * on const -> " << *ft_it << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_it << std::endl;
	std::cout << "Test ft : operaotr * on const -> " << *ft_itend << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operaotr * on const -> " << *std_itend << std::endl;
	testBool(true);
}

int
test_vector_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
		ft::vector<int>		ft_c0;
		std::vector<int>	std_c0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in vector 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 1; i < testSize; i++)	{
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
		test_constReverseIterator(ft_c0, std_c0);
	}
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		// std::vector<int>			s;
		// s.reserve(20);
		// s.push_back(42);
		// s.push_back(1);
		// s.push_back(2);
		// s.push_back(3);
		// s.push_back(4);
		// s.push_back(5);
		// std::vector<int>::reverse_iterator s_rit = s.rbegin();
		// std::vector<int>::reverse_iterator s_rite = s.rend();
		// std::cout << "BASE rev begin : " <<	*(s.begin()) << std::endl;
		// std::cout << "BASE rev end   : " <<	*(s.end())	 << std::endl;
		// std::cout << "BASE rev rbegin  : " <<	*s_rit	 << std::endl;
		// std::cout << "BASE rev rend    : " <<	*s_rite	 << std::endl;
		// s_rit++;
		// s_rit++;
		// s_rite--;
		// s_rite--;

		// std::cout << "BASE rev rbegin ++ : " <<	*s_rit	 << std::endl;
		// std::cout << "BASE rev rend --   : " <<	*s_rite	 << std::endl;
		// std::cout << "BASE rev rbegin ++ base : " <<	*(s_rit.base())	 << std::endl;
		// std::cout << "BASE rev rend -- base   : " <<	*(s_rite.base())	 << std::endl;


		// exit(1);

		// ft::vector<int>			l;
		// l.push_back(0);
		// l.push_back(1);
		// l.push_back(2);
		// l.push_back(3);
		// l.push_back(4);
		// l.push_back(5);
		// ft::vector<int>::reverse_iterator l_rit = l.rbegin();
		// l_rit++;
		// l_rit++;
		// ft::vector<int>::reverse_iterator l_rite = l.rend();
		// l_rite--;
		// l_rite--;

		// testBool(*(l_rit.base()) == *(s_rit.base()), __LINE__);
		// testBool(*(l_rite.base()) == *(s_rite.base()), __LINE__);
		// testBool(*l_rite == *s_rite, __LINE__);
		// testBool(*l_rit == *s_rit, __LINE__);
	}
	return (0);
}
