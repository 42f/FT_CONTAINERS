/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_iterator.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:38 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/23 09:01:38 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

void
test_constIterator( ft::map<int, int>  & ft_c0, std::map<int, int> & std_c0 )	{

	std::cout << HEADER_TITLE << "Test const version of reverse iterator" << RESET_COLOR << std::endl;
	std::cout << SUBTITLE << "If compile fails, const version of function are missing" << RESET_COLOR << std::endl;

	std::map<int, int>::const_iterator	std_it = std_c0.begin();
	std::map<int, int>::const_iterator	std_itend = --std_c0.end();

	ft::map<int, int>::const_iterator		ft_it = ft_c0.begin(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	ft::map<int, int>::const_iterator		ft_itend = --ft_c0.end(); //  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !

	std::cout << "Test ft : operator-> on const iterator: " << ft_it->first << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operator-> on const iterator: " << std_it->first << std::endl;
	std::cout << "Test ft : operator-> on const iterator: " << ft_itend->first << std::endl;//  !!!! ---> HINT:  IN CASE OF COMPILER ISSUE: const version is MISSING !
	std::cout << "Test std: operator-> on const iterator: " << std_itend->first << std::endl;
	// ++std_it;
	// std::cout <<  << std::endl;std::cout << "it ++ -> " << std_it->first << std::endl;
	// ft_it++;
	testBool(true);
}

int
test_map_iterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << " [ Iterator Ctors ] " << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Default Ctor, copy ctor, copy assignable ]" << RESET_COLOR << std::endl;

		std::map<int,int> 				std_c0;
		ft::map<int,int> 				ft_c0;

		// insert some values:
		std_c0[1]= 42 ;
		std_c0[0] = 0;
		std_c0[-4] = 21;

		ft_c0[1]= 42 ;
		ft_c0[0] = 0;
		ft_c0[-4] = 21;

		std::map<int, int>::iterator		std_it_1 = std_c0.begin();
		ft::map<int, int>::iterator			ft_it_1 = ft_c0.begin();


		std::cout << SUBTITLE << "[ Change some mapped values through iterator ]" << RESET_COLOR << std::endl;
		std_it_1->second = 21;
		ft_it_1->second = 21;

		std::map<int, int>::iterator		std_it_2(std_it_1);
		ft::map<int, int>::iterator			ft_it_2(ft_it_1);
		std::map<int, int>::iterator		std_it_3;
		ft::map<int, int>::iterator			ft_it_3;
		std_it_3 = std_it_1;
		ft_it_3 = ft_it_1;
		testBool(std_it_1->first == ft_it_1->first && std_it_1->second == ft_it_1->second, __LINE__);
		testBool(std_it_2->first == ft_it_2->first && std_it_2->second == ft_it_2->second, __LINE__);
		testBool(std_it_3->first == ft_it_3->first && std_it_3->second == ft_it_3->second, __LINE__);

		test_constIterator(ft_c0, std_c0);

	}

	return (0);
}
