/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_reverseIterator.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:02:26 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/24 10:40:05 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_list.hpp"

int
test_list_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR RELATIONAL OPERATORS" << RESET_COLOR << std::endl;
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 1; i <= testSize; i++)	{
			ftl0.push_back(i);
			stdl0.push_back(i);
		}
		ftl0.push_back(42);
		stdl0.push_back(42);
		testList(ftl0, stdl0, NOPRINT);

		ft::list<int>::reverse_iterator		ft_it = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_it2 = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_itend = ftl0.rend();

		std::list<int>::reverse_iterator		std_it = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_it2 = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_itend = stdl0.rend();


		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
	}
	std::cout << HEADER_TITLE << "TEST REVERSE ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{

		std::list<int>			s;
		s.push_back(0);
		s.push_back(1);
		s.push_back(2);
		s.push_back(3);
		s.push_back(4);
		s.push_back(5);
		std::list<int>::reverse_iterator s_rit = s.rbegin();
		s_rit++;
		s_rit++;
		std::list<int>::reverse_iterator s_rite = s.rend();
		s_rite--;
		s_rite--;

		ft::list<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::list<int>::reverse_iterator l_rit = l.rbegin();
		l_rit++;
		l_rit++;
		ft::list<int>::reverse_iterator l_rite = l.rend();
		l_rite--;
		l_rite--;

		testBool(*(l_rit.base()) == *(s_rit.base()), __LINE__);
		testBool(*(l_rite.base()) == *(s_rite.base()), __LINE__);
		testBool(*l_rite == *s_rite, __LINE__);
		testBool(*l_rit == *s_rit, __LINE__);
	}
	return (0);
}
