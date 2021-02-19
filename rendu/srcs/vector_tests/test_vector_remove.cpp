/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_remove.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:50 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 15:36:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_remove( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty list ]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c0;
		std::list<int>	std_c0;
		size_t			testSize = 3000000;
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove with value = 42 (on empty list)]" << RESET_COLOR << std::endl;
		ft_c0.remove(42);
		std_c0.remove(42);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ pushback " << testSize << " random values in list (same value for ft and std list, 0 <= val < 20) ]" << RESET_COLOR << std::endl;


		srand(reinterpret_cast<long unsigned int>(&std_c0));
		int val;
		for (size_t i = 0; i < testSize; i++)	{
			val = rand() % 20;
			ft_c0.push_back(val);
			std_c0.push_back(val);
		}
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove with the last value pushed in the list ]" << RESET_COLOR << std::endl;
		ft_c0.remove(val);
		std_c0.remove(val);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ remove with valus which is not contained in list (42) ]" << RESET_COLOR << std::endl;
		ft_c0.remove(42);
		std_c0.remove(42);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate a list of 5 elements, all 42]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c0(5, 42);
		std::list<int>	std_c0(5, 42);
		testVector(ft_c0, std_c0, NOPRINT);
		ft_c0.remove(42);
		std_c0.remove(42);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
