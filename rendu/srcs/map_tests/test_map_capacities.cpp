/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_capacities.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:48:58 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 5;

		std::cout << HEADER_TITLE << "[ Empty / size on empty map ]" << RESET_COLOR << std::endl;
		std::map<int, int>		std_c0;
		ft::map<int, int>		ft_c0;
		testBool(std_c0.empty() == ft_c0.empty(), __LINE__);
		testBool(std_c0.size() == ft_c0.size(), __LINE__);

		std::cout << HEADER_TITLE << "[ Empty / size on non empty map ]" << RESET_COLOR << std::endl;
		for(int i = 0; i < static_cast<int>(testSize); i++)	{
			std_c0[i] = 1;
			ft_c0[i] = 1;
			testBool(std_c0.empty() == ft_c0.empty(), __LINE__, i);
			testBool(std_c0.size() == ft_c0.size(), __LINE__, i);
		}

		std::cout << HEADER_TITLE << "[ max_size, only test if present, values might differ ]" << RESET_COLOR << std::endl;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::map<char, std::string>		std_c0;
		ft::map<char, std::string>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << " <char, std::string> : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << " <char, std::string> : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::map<std::string, u_int64_t>		std_c0;
		ft::map<std::string, u_int64_t>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << " <std::string, u_int64_t> : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << " <std::string, u_int64_t> : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::map<float, double>		std_c0;
		ft::map<float, double>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << " <float, double> : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << " <float, double> : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::map<std::vector<float>, char*>		std_c0;
		ft::map<std::vector<float>, char*>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << " <std::vector<float>, char*> : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << " <std::vector<float>, char*> : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::map<short, int>		std_c0;
		ft::map<short, int>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << " <short, int> : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << " <short, int> : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	return (0);
}
