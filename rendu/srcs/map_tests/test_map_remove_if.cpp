/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_remove_if.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:59 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

int
test_map_remove_if( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<int>	ft_c0;
		std::map<int>	std_c0;
		size_t			testSize = 3000000;
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>10 ]" << RESET_COLOR << std::endl;
		ft_c0.remove_if(more_than_10);
		std_c0.remove_if(more_than_10);
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ pushback " << testSize << " random values in map (same value for ft and std map, 0 <= val < 20) ]" << RESET_COLOR << std::endl;


		srand(reinterpret_cast<long unsigned int>(&std_c0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ft_c0.push_back(val);
			std_c0.push_back(val);
		}
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>100 (no element will be removed) ]" << RESET_COLOR << std::endl;
		ft_c0.remove_if(more_than_100);
		std_c0.remove_if(more_than_100);
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>10 ]" << RESET_COLOR << std::endl;
		ft_c0.remove_if(more_than_10);
		std_c0.remove_if(more_than_10);
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value<=10 ]" << RESET_COLOR << std::endl;
		ft_c0.remove_if(less_or_eq_10);
		std_c0.remove_if(less_or_eq_10);
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ same as before but map 0 is now empty ]" << RESET_COLOR << std::endl;
		ft_c0.remove_if(less_or_eq_10);
		std_c0.remove_if(less_or_eq_10);
		testMap(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
