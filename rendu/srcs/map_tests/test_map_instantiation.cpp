/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_instantiation.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:31 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:17:25 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_instantiation( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << TITLE << "~~~~ To see constructor calls, compile with " << RESET_COLOR << "-> make debug_mode=1 re f "<< std::endl;

		std::map<const int, float>	std_c0;

		(void)std_c0;

		/*
	{

		std::cout << SUBTITLE << "[ DEFAULT CONSTRUCTOR ]" << RESET_COLOR << std::endl;
		{
			ft::map<std::string>	ft_c0;
			std::map<std::string>	std_c0;
			testMap(ft_c0, std_c0, NOPRINT);
			ft::map<float>		ft_c1;
			std::map<float>	std_c1;
			testMap(ft_c1, std_c1, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(5, 123);
			std::map<int>	std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value explicitly casted ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(static_cast<size_t>(5),123);
			std::map<int>	std_c0(static_cast<size_t>(5),123);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(5);
			std::map<int>	std_c0(5);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value and with classExample which has a default value ]" << RESET_COLOR << std::endl;
		{
			ft::map<exampleClass>	ft_c0(5);
			std::map<exampleClass>	std_c0(5);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ RANGE CONSTRUCTOR test: map0 with fill and map1 with range ctor from map0 iterators ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>		ft_c0(5, 123);
			std::map<int>	std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);
			std::cout << SUBTITLE << "->>\t\t[ RANGE CONSTRUCTOR with begin and ++begin as argument ]" << RESET_COLOR << std::endl;
			ft::map<int>		ft_c1(ft_c0.begin(), ++ft_c0.begin());
			std::map<int>	std_c1(std_c0.begin(), ++std_c0.begin());
			testMap(ft_c1, std_c1, NOPRINT);

		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from map with 5 elements]" << RESET_COLOR << std::endl;
		{
			ft::map<int>			ft_c0(5, 123);
			std::map<int>		std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);

			ft::map<int>			ft_c1(ft_c0);
			std::map<int>		std_c1(std_c0);
			testMap(ft_c1, std_c1, NOPRINT);

			std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
			testBool(&(*ft_c0.begin()) != &(*ft_c1.begin()), __LINE__);
			testBool(&(*std_c0.begin()) != &(*std_c1.begin()), __LINE__);
		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from map with no elements]" << RESET_COLOR << std::endl;
		{
			ft::map<int>		ft_c0;
			std::map<int>	std_c0;

			ft::map<int>		ft_c1(ft_c0);
			std::map<int>	std_c1(std_c0);
			testMap(ft_c0, std_c0, NOPRINT);
			testMap(ft_c1, std_c1, NOPRINT);
		}
	}
	*/
	return (0);
}
