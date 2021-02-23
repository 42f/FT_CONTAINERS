/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_reverse.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:35 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_reverse( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::map<int>		ft_c0;
		std::map<int>		std_c0;
		size_t				testSize = 6;


		for (size_t i = 1; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
		}
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << HEADER_TITLE << "map FILLED WITH "<< testSize << " DESCENDING VALUES " << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ft_c0.reverse();
		std_c0.reverse();
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 1 value in map, increasing size by 1, chaging oddness ]" << RESET_COLOR << std::endl;
		ft_c0.push_back(42);
		std_c0.push_back(42);
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ft_c0.reverse();
		std_c0.reverse();
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		ft::map<int>		ft_c0;
		std::map<int>		std_c0;
		srand(reinterpret_cast<long unsigned int>(&std_c0));
		size_t				testSize = rand() % 5000000;


		for (size_t i = 1; i < testSize; i++)	{
			int val = rand() % 100;
			ft_c0.push_back(val);
			std_c0.push_back(val);
		}
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << HEADER_TITLE << "map FILLED WITH "<< testSize << " VALUES, A RANDOM NUMBER OF RANDOM VALUES " << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ft_c0.reverse();
		std_c0.reverse();
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 1 value in map, increasing size by 1, chaging oddness ]" << RESET_COLOR << std::endl;
		ft_c0.push_back(42);
		std_c0.push_back(42);
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ft_c0.reverse();
		std_c0.reverse();
		testMap(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}

