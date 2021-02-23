/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_nonmember_swap.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:27 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/22 16:01:29 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_nonmember_swap( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate map0 of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::map<int>		ft_c0(3, -1);
		std::map<int>	std_c0(3, -1);
		testMap(ft_c0, std_c0, NOPRINT);


		std::cout << SUBTITLE << "[ Instanciate map1 of 3 elements value 42 + push front 0 + push back 99 ]" << RESET_COLOR << std::endl;
		ft::map<int>	ft_c1(3, 42);
		std::map<int>	std_c1(3, 42);
		ft_c1.insert(ft_c1.begin(), 0);
		std_c1.insert(std_c1.begin(), 0);
		ft_c1.push_back(99);
		std_c1.push_back(99);
		testMap(ft_c1, std_c1, NOPRINT);

		ft::map<int>::iterator		ft_it0 = ft_c0.begin();
		ft::map<int>::iterator		ft_it1 = ft_c1.begin();
		std::map<int>::iterator		std_it0 = std_c0.begin();
		std::map<int>::iterator		std_it1 = std_c1.begin();

		std::cout << SUBTITLE << "[ swap 2 maps ]" << RESET_COLOR << std::endl;
		ft::swap(ft_c0, ft_c1);
		std::swap(std_c0, std_c1);
		testMap(ft_c0, std_c0, NOPRINT, "Test map0");
		testMap(ft_c1, std_c1, NOPRINT, "Test map1");

		std::cout << SUBTITLE << "[ test if iterator stayed valid while pointing to new values ]" << RESET_COLOR << std::endl;
		testBool(&(*ft_it0) == &(*ft_c1.begin()), __LINE__);
		testBool(&(*ft_it1) == &(*ft_c0.begin()), __LINE__);
		testBool(&(*std_it0) == &(*std_c1.begin()), __LINE__);
		testBool(&(*std_it1) == &(*std_c0.begin()), __LINE__);

		std::cout << SUBTITLE << "[ assign map 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ft_c1.assign(10, 99);
		std_c1.assign(10, 99);
		testMap(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 maps ]" << RESET_COLOR << std::endl;
		ft::swap(ft_c0, ft_c1);
		std::swap(std_c0, std_c1);
		testMap(ft_c0, std_c0, NOPRINT, "Test map0");
		testMap(ft_c1, std_c1, NOPRINT, "Test map1");


		std::cout << SUBTITLE << "[ assign map 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ft_c1.assign(10, 99);
		std_c1.assign(10, 99);
		testMap(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 maps ]" << RESET_COLOR << std::endl;
		ft::swap(ft_c0, ft_c1);
		std::swap(std_c0, std_c1);
		testMap(ft_c0, std_c0, NOPRINT, "Test map0");
		testMap(ft_c1, std_c1, NOPRINT, "Test map1");

		std::cout << SUBTITLE << "[ clear map0 ]" << RESET_COLOR << std::endl;
		ft_c0.clear();
		std_c0.clear();
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 maps ]" << RESET_COLOR << std::endl;
		ft::swap(ft_c0, ft_c1);
		std::swap(std_c0, std_c1);
		testMap(ft_c0, std_c0, NOPRINT, "Test map0");
		testMap(ft_c1, std_c1, NOPRINT, "Test map1");
	}
	return (0);
}
