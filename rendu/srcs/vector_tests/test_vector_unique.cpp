/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_unique.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:08 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 15:36:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_unique( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with doubles ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<double>	ft_c0;
		std::list<double>	std_c0;
		size_t				testSize = 500000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random float values in list (same value for ft and std list, 0 <= val < 5) ]" << RESET_COLOR << std::endl;
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
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (1) no arg ]" << RESET_COLOR << std::endl;
		testVector(ft_c0, std_c0, NOPRINT);
		std_c0.unique();
		ft_c0.unique();
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as boolean function (same_integral_part) ]" << RESET_COLOR << std::endl;
		std_c0.unique(same_integral_part);
		ft_c0.unique(same_integral_part);
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as a structure (is_near()) ]" << RESET_COLOR << std::endl;
		std_c0.unique(is_near());
		ft_c0.unique(is_near());
		testVector(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
