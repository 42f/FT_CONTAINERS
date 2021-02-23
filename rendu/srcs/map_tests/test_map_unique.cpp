/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_unique.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:08 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_unique( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with doubles ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::map<double>	ft_c0;
		std::map<double>	std_c0;
		size_t				testSize = 500000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random float values in map (same value for ft and std map, 0 <= val < 5) ]" << RESET_COLOR << std::endl;
		srand(reinterpret_cast<long unsigned int>(&std_c0));

		int		divider;
		float	val;
		for (size_t i = 0; i < testSize; i++)	{
			if (i < (testSize / 3) || i > (testSize / 2))	{
				divider = rand() % 5;
				val = static_cast<float>(rand() % 15) / ( (divider == 0) ? i + 1 : divider );
			}
			ft_c0.push_back(val);
			std_c0.push_back(val);
		}
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (1) no arg ]" << RESET_COLOR << std::endl;
		testMap(ft_c0, std_c0, NOPRINT);
		std_c0.unique();
		ft_c0.unique();
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as boolean function (same_integral_part) ]" << RESET_COLOR << std::endl;
		std_c0.unique(same_integral_part);
		ft_c0.unique(same_integral_part);
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as a structure (is_near()) ]" << RESET_COLOR << std::endl;
		std_c0.unique(is_near());
		ft_c0.unique(is_near());
		testMap(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
