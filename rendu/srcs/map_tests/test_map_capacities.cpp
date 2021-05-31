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

# include "./tester/exampleClass.hpp"
# include "./tester/bvaletteTester_map.hpp"

template < typename T, typename U>
void
test_max_size()	{
	std::map<T, U>	std_c0;
	ft::map<T, U>		ft_c0;
	if (testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__) != true)
		std::cout << ERROR_TITLE << "Sizes returned : ft("<< ft_c0.max_size() <<") std("<< std_c0.max_size() <<")" << RESET_COLOR << std::endl;
}

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
	}
	std::cout << HEADER_TITLE << "[ Max Size with various types ]" << RESET_COLOR << std::endl;
	test_max_size<bool, int>();
	test_max_size<short, int>();
	test_max_size<char, int>();
	test_max_size<int, int>();
	test_max_size<float, int>();
	test_max_size<double, int>();
	test_max_size<std::string, int>();
	test_max_size<exampleClass, int>();
	test_max_size<int, bool>();
	test_max_size<int, short>();
	test_max_size<int, char>();
	test_max_size<int, int>();
	test_max_size<int, float>();
	test_max_size<int, double>();
	test_max_size<int, std::string>();
	test_max_size<int, exampleClass>();
	return (0);
}
