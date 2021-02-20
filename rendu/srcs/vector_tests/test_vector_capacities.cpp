/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_capacities.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:48:58 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 0;
		std::cout << HEADER_TITLE << "[ Empty() on vector with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::vector<int>	std(testSize);
		ft::vector<int>		ft(testSize);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		testBool(std.empty() == ft.empty(), __LINE__);
	}
	{
		size_t		testSize = 5;
		std::cout << HEADER_TITLE << "[ Size and capacity on vector with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::vector<int>	std(testSize);
		ft::vector<int>	ft(testSize);

		std::cout << "Size of std : " << std.size() << std::endl;
		std::cout << "Size of ft  : " << ft.size() << std::endl;

		testBool(std.size() == ft.size(), __LINE__);
		testBool(std.capacity() >= std.size() && ft.capacity() >= ft.size(), __LINE__);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		testBool(std.empty() == ft.empty(), __LINE__);
	}
	{
		size_t		testSize = 0;
		std::cout << HEADER_TITLE << "[ max_size for a vector of " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::vector<float>		std(testSize);
		ft::vector<float>		ft(testSize);
		std::cout << "max_size for std : " << std.max_size() << std::endl;
		std::cout << "max_size for ft  : " << ft.max_size() << std::endl;
		testBool(std.max_size() == ft.max_size(), __LINE__);

	}
	return (0);
}
