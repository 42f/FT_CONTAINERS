/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_capacities.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 08:43:18 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/17 11:18:41 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_list.hpp"

int
test_list_capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		testBool(std.empty() == ft.empty(), __LINE__);
	}
	{
		size_t		testSize = 5;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "Size of std : " << std.size() << std::endl;
		std::cout << "Size of ft  : " << ft.size() << std::endl;

		testBool(std.size() == ft.size(), __LINE__);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		testBool(std.empty() == ft.empty(), __LINE__);
	}
	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ max_size for a list of " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<bool>	std(testSize);
		ft::list<bool>		ft(testSize);
		testBool(std.max_size() == ft.max_size(), __LINE__);
		std::cout << "bool : max_size for std : " << std.max_size() << std::endl;
		std::cout << "bool : max_size for ft  : " << ft.max_size() << std::endl;

	}
	{
		std::list<char>		std_c0;
		ft::list<char>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "char : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "char : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::list<std::string>		std_c0;
		ft::list<std::string>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "std::string : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "std::string : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::list<float>		std_c0;
		ft::list<float>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "float : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "float : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::list<int>		std_c0;
		ft::list<int>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "int : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "int : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::list<short>		std_c0;
		ft::list<short>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "short : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "short : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::list<double>		std_c0;
		ft::list<double>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "double : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "double : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}

	return (0);
}
