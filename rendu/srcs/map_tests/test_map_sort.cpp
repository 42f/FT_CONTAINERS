/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_sort.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:20 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_sort( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "map FILLED WITH A RANDOM NUMBER OF RANDOM VALUES" << RESET_COLOR << std::endl;
	{
		ft::map<int>		ft_c0;
		std::map<int>		std_c0;
		srand(reinterpret_cast<long unsigned int>(&std_c0));
		size_t				testSize = rand() % 15000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into map 0]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 10000;
			ft_c0.push_back(val);
			std_c0.push_back(val);
		}
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ sort map 0 with greater_than Compare ]" << RESET_COLOR << std::endl;
		ft_c0.sort(greater_than);
		std_c0.sort(greater_than);
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ sort map 0 with not argument ]" << RESET_COLOR << std::endl;
		ft_c0.sort();
		std_c0.sort();
		testMap(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}

