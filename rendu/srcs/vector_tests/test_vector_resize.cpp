/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_resize.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:42 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:31:14 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

void
testReserve(size_t testReserve, ft::vector<int> & ft_c0, std::vector<int> & std_c0)	 {
		std::cout << SUBTITLE << "[ reserve("<< testReserve << ") ]" << RESET_COLOR << std::endl;

		ft_c0.reserve(testReserve);
		std_c0.reserve(testReserve);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
		testBool(ft_c0.capacity() >= testReserve && std_c0.capacity() >= testReserve, __LINE__);
}

int
test_vector_resize( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ Resize() ]" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ Instanciate vector of 3 elements with no value ]" << RESET_COLOR << std::endl;
		ft::vector<int>	ft_c0(3);
		std::vector<int>	std_c0(3);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to same size with no value ]" << RESET_COLOR << std::endl;
		ft_c0.resize(3);
		std_c0.resize(3);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 5 with no value ]" << RESET_COLOR << std::endl;
		ft_c0.resize(5);
		std_c0.resize(5);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 7 with value 42 ]" << RESET_COLOR << std::endl;
		ft_c0.resize(7, 42);
		std_c0.resize(7, 42);
		testVector(ft_c0, std_c0, NOPRINT);
		// std::cout << SUBTITLE << "[ push back 999 and push front 111 ]" << RESET_COLOR << std::endl;
		// ft_c0.push_back(999);
		// std_c0.push_back(999);
		// ft_c0.push_front(111);
		// std_c0.push_front(111);
		// testVector(ft_c0, std_c0, NOPRINT);
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

		size_t testResize = std_c0.max_size() + 1;
		std::cout << SUBTITLE << "[ resize("<< testResize << ") Max size, will throw exception ]" << RESET_COLOR << std::endl;
		try {
			try { std_c0.resize(testResize); } catch ( std::exception & e) {};
			ft_c0.resize(testResize);
			testBool( 1 == 2, __LINE__);
		}
		catch (  std::bad_alloc & e )	{
			std::cout << "Exception thrown by ft::vector, as it should." << std::endl;
			testBool( 1 == 1, __LINE__);
		}
	}
	{
		std::cout << HEADER_TITLE << "[ Reserve() ]" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ Instanciate vector of 3 elements with no value ]" << RESET_COLOR << std::endl;

		ft::vector<int>		ft_c0(3);
		std::vector<int>	std_c0(3);
		testVector(ft_c0, std_c0, NOPRINT);

		testReserve(3, ft_c0, std_c0);
		testReserve(100, ft_c0, std_c0);
		testReserve(5, ft_c0, std_c0);
		testReserve(0, ft_c0, std_c0);

		size_t sizeReserve = std_c0.max_size() + 1;
		std::cout << SUBTITLE << "[ reserve("<< sizeReserve << ") Max size, will throw exception ]" << RESET_COLOR << std::endl;
		try {
			try { std_c0.reserve(sizeReserve); } catch ( std::exception & e) {};
			ft_c0.reserve(sizeReserve);
			testBool( 1 == 2, __LINE__);
		}
		catch (  std::bad_alloc & e )	{
			std::cout << "Exception thrown by ft::vector, as it should." << std::endl;
			testBool( 1 == 1, __LINE__);
		}
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
	}
	return (0);
}
