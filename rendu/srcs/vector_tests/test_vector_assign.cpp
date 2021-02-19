/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_assign.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:48:00 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 14:22:40 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_assign( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c0(3, -1);
		std::list<int>	std_c0(3, -1);
		testList(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 5 with value 42 ]" << RESET_COLOR << std::endl;
		ft_c0.assign(5, 42);
		std_c0.assign(5, 42);
		testList(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 99 ]" << RESET_COLOR << std::endl;
		ft_c0.assign(1, 99);
		std_c0.assign(1, 99);
		testList(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 100 ]" << RESET_COLOR << std::endl;
		ft_c0.assign(1, 100);
		std_c0.assign(1, 100);
		testList(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ assign with Iterators from list containing 3 times value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c1(3, -1);
		std::list<int>	std_c1(3, -1);
		ft_c1.push_front(42);
		std_c1.push_front(42);
		ft_c1.push_back(99);
		std_c1.push_back(99);
		ft_c0.assign(ft_c1.begin(), ft_c1.end());
		std_c0.assign(std_c1.begin(), std_c1.end());
		testList(ft_c0, std_c0, NOPRINT);

	}
	return (0);
}
