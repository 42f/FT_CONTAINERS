/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_instantiation.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:31 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 18:47:35 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_instantiation( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << TITLE << "~~~~ To see constructor calls, compile with " << RESET_COLOR << "-> make debug_mode=1 re f "<< std::endl;
	{

		{
			std::vector<int>	c1(10, 42);
			ft::vector<int>		c0(10, 42);
			putVector(c1);
			putVector(c0);
			c1.resize(c1.capacity() + 5);
			c0.resize(c0.capacity() + 5);
			putVector(c1);
			putVector(c0);
		}
		return (0);

		std::cout << SUBTITLE << "[ DEFAULT CONSTRUCTOR ]" << RESET_COLOR << std::endl;
		{
			ft::vector<std::string>	ft_c0;
			std::vector<std::string>	std_c0;
			testVector(ft_c0, std_c0, NOPRINT);
			ft::vector<float>		ft_c1;
			std::vector<float>	std_c1;
			testVector(ft_c1, std_c1, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>	ft_c0(5, 123);
			std::vector<int>	std_c0(5, 123);
			testVector(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value explicitly casted ]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>	ft_c0(static_cast<size_t>(5),123);
			std::vector<int>	std_c0(static_cast<size_t>(5),123);
			testVector(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value ]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>	ft_c0(5);
			std::vector<int>	std_c0(5);
			testVector(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value and with classExample which has a default value ]" << RESET_COLOR << std::endl;
		{
			ft::vector<exampleClass>	ft_c0(5);
			std::vector<exampleClass>	std_c0(5);
			testVector(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ RANGE CONSTRUCTOR test: list0 with fill and list1 with range ctor from list0 iterators ]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>		ft_c0(5, 123);
			std::vector<int>	std_c0(5, 123);
			testVector(ft_c0, std_c0, NOPRINT);
			std::cout << SUBTITLE << "->>\t\t[ RANGE CONSTRUCTOR with begin and ++begin as argument ]" << RESET_COLOR << std::endl;
			ft::vector<int>		ft_c1(ft_c0.begin(), ++ft_c0.begin());
			std::vector<int>	std_c1(std_c0.begin(), ++std_c0.begin());
			testVector(ft_c1, std_c1, NOPRINT);

		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with 5 elements]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>			ft_c0(5, 123);
			std::vector<int>		std_c0(5, 123);
			testVector(ft_c0, std_c0, NOPRINT);

			ft::vector<int>			ft_c1(ft_c0);
			std::vector<int>		std_c1(std_c0);
			testVector(ft_c1, std_c1, NOPRINT);

			std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
			testBool(&(*ft_c0.begin()) != &(*ft_c1.begin()), __LINE__);
			testBool(&(*std_c0.begin()) != &(*std_c1.begin()), __LINE__);
		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with no elements]" << RESET_COLOR << std::endl;
		{
			ft::vector<int>		ft_c0;
			std::vector<int>	std_c0;

			ft::vector<int>		ft_c1(ft_c0);
			std::vector<int>	std_c1(std_c0);
			testVector(ft_c0, std_c0, NOPRINT);
			testVector(ft_c1, std_c1, NOPRINT);
		}
	}
	return (0);
}
