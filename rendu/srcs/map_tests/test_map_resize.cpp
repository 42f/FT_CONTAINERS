/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_resize.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:42 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/22 16:56:36 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

#define NOVALUE -1

void
testReserve(size_t testSize, ft::map<int> & ft_c0, std::map<int> & std_c0)	 {
		std::cout << SUBTITLE << "[ reserve("<< testSize << ") ]" << RESET_COLOR << std::endl;

		ft_c0.reserve(testSize);
		std_c0.reserve(testSize);
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
		testBool(ft_c0.capacity() >= testSize && std_c0.capacity() >= testSize, __LINE__);
}

void
testResize(ft::map<int> & ft_c0, std::map<int> & std_c0, size_t testSize, int value = NOVALUE)	 {

		if (value == NOVALUE)
			std::cout << SUBTITLE << "[ resize to " << testSize << " with no value ]" << RESET_COLOR << std::endl;
		else
			std::cout << SUBTITLE << "[ resize to " << testSize << " with value " << value << " ]" << RESET_COLOR << std::endl;

		ft_c0.resize(testSize, value);
		std_c0.resize(testSize, value);
		testMap(ft_c0, std_c0, NOPRINT);
}

int
test_map_resize( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ Resize() ]" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ Instanciate map of 3 elements with no value ]" << RESET_COLOR << std::endl;
		ft::map<int>	ft_c0(3);
		std::map<int>	std_c0(3);
		testMap(ft_c0, std_c0, NOPRINT);

		testResize(ft_c0, std_c0, 3);
		testResize(ft_c0, std_c0, 5);
		testResize(ft_c0, std_c0, 7);
		std::cout << SUBTITLE << "[ push back 999 ]" << RESET_COLOR << std::endl;
		ft_c0.push_back(999);
		std_c0.push_back(999);
		testMap(ft_c0, std_c0, NOPRINT);

		testResize(ft_c0, std_c0, 3);
		testResize(ft_c0, std_c0, 3);
		testResize(ft_c0, std_c0, 3, 21);
		testResize(ft_c0, std_c0, 5, 42);
		testResize(ft_c0, std_c0, 7, 42);
		testResize(ft_c0, std_c0, 4, 99);
		testResize(ft_c0, std_c0, 4, 42);
		testResize(ft_c0, std_c0, 4);
		testResize(ft_c0, std_c0, 1000000);
		testResize(ft_c0, std_c0, ft_c0.capacity() + 1);
		testResize(ft_c0, std_c0, 0);

		size_t testResize = std_c0.max_size();
		std::cout << SUBTITLE << "[ resize("<< testResize << ") Max size, will throw exception ]" << RESET_COLOR << std::endl;
		try {
			try { std_c0.resize(testResize); }
				catch ( std::exception & e) {}
				catch ( std::bad_alloc & e) {}
			ft_c0.resize(testResize);
			testBool( false, __LINE__);
		}
		catch (  std::bad_alloc & e )	{
			std::cout << "Exception thrown: std::bad_alloc, as it should." << std::endl;
			testBool( true, __LINE__);
		}
		catch (  std::exception & e )	{
			std::cout << "Exception thrown: std::exception, should be bad_alloc but it's ok..." << std::endl;
			testBool( true, __LINE__);
		}
		catch (  std::length_error & e )	{
			std::cout << "Exception thrown: std::length_error, Wrong !" << std::endl;
			testBool( false, __LINE__);
		}
	}
	{
		std::cout << HEADER_TITLE << "[ Reserve() ]" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ Instanciate map of 3 elements with no value ]" << RESET_COLOR << std::endl;

		ft::map<int>		ft_c0(3);
		std::map<int>	std_c0(3);
		testMap(ft_c0, std_c0, NOPRINT);

		testReserve(3, ft_c0, std_c0);
		testReserve(100, ft_c0, std_c0);
		testReserve(5, ft_c0, std_c0);
		testReserve(0, ft_c0, std_c0);

		size_t sizeReserve = std_c0.max_size() + 1;
		std::cout << SUBTITLE << "[ reserve("<< sizeReserve << ") Max size, will throw exception ]" << RESET_COLOR << std::endl;
		try {
			try { std_c0.reserve(sizeReserve); } catch ( std::exception & e) {};
			ft_c0.reserve(sizeReserve);
			std::cout << "No Exception was thrown ! It should have !" << std::endl;
			testBool( false, __LINE__);
		}
		catch (  std::length_error & e )	{
			std::cout << "Exception thrown: std::length_error, as it should." << std::endl;
			testBool( true, __LINE__);
		}
		catch (  std::bad_alloc & e )	{
			std::cout << "Exception thrown: std::bad_alloc, should be length_error but it's ok..." << std::endl;
			testBool( true, __LINE__);
		}
		catch (  std::exception & e )	{
			std::cout << "Exception thrown: std::exception, should be length_error but it's ok..." << std::endl;
			testBool( true, __LINE__);
		}
		testMap(ft_c0, std_c0, NOPRINT);
		std::cout << "New Capacities after reserve: ft(" << ft_c0.capacity() << ") ; std(" << std_c0.capacity() << ")" << std::endl;
	}
	return (0);
}
