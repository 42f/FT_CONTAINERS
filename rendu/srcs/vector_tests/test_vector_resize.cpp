/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_resize.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:42 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 15:36:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_resize( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list of 3 elements with no value ]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c0(3);
		std::list<int>	std_c0(3);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 5 with no value ]" << RESET_COLOR << std::endl;
		ft_c0.resize(5);
		std_c0.resize(5);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 7 with value 42 ]" << RESET_COLOR << std::endl;
		ft_c0.resize(7, 42);
		std_c0.resize(7, 42);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 999 and push front 111 ]" << RESET_COLOR << std::endl;
		ft_c0.push_back(999);
		std_c0.push_back(999);
		ft_c0.push_front(111);
		std_c0.push_front(111);
		std::cout << SUBTITLE << "[ resize to 3 with value 42 ]" << RESET_COLOR << std::endl;
		ft_c0.resize(3, 42);
		std_c0.resize(3, 42);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 4 with value 42 ]" << RESET_COLOR << std::endl;
		ft_c0.resize(4, 42);
		std_c0.resize(4, 42);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 4 with value 99 ]" << RESET_COLOR << std::endl;
		ft_c0.resize(4, 99);
		std_c0.resize(4, 99);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 0 with no value ]" << RESET_COLOR << std::endl;
		ft_c0.resize(0);
		std_c0.resize(0);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
