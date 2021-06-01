/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_capacities.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:56:19 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/01 10:32:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/exampleClass.hpp"
# include "./tester/bvaletteTester_map.hpp"

template < typename T, typename U>
void
test_max_size()	{
	std::map<T, U>	std_c0;
	ft::map<T, U>		ft_c0;
	try {
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
	}
	catch (failedTest &e) {
		std::cout << ERROR_TITLE << "Sizes returned : ft("<< ft_c0.max_size() <<") std("<< std_c0.max_size() <<")" << RESET_COLOR << std::endl;
		throw failedTest();
	}
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
	std::cout << "Test <bool, int>		: ";				test_max_size<bool, int>();
	std::cout << "Test <short, int>		: ";				test_max_size<short, int>();
	std::cout << "Test <char, int>		: ";				test_max_size<char, int>();
	std::cout << "Test <int, int>		: ";				test_max_size<int, int>();
	std::cout << "Test <float, int>		: ";				test_max_size<float, int>();
	std::cout << "Test <double, int>	: ";				test_max_size<double, int>();
	std::cout << "Test <std::string, int>	: ";		test_max_size<std::string, int>();
	std::cout << "Test <exampleClass, int>	: ";		test_max_size<exampleClass, int>();
	std::cout << "Test <int, bool>			: ";				test_max_size<int, bool>();
	std::cout << "Test <int, short>			: ";				test_max_size<int, short>();
	std::cout << "Test <int, char>			: ";				test_max_size<int, char>();
	std::cout << "Test <int, int>			: ";				test_max_size<int, int>();
	std::cout << "Test <int, float>			: ";				test_max_size<int, float>();
	std::cout << "Test <int, double>		: ";				test_max_size<int, double>();
	std::cout << "Test <int, std::string>	: ";		test_max_size<int, std::string>();
	std::cout << "Test <int, exampleClass>	: ";		test_max_size<int, exampleClass>();

	// -- requires node specialization
	// std::cout << "Test <bool, short>			: ";			test_max_size<bool, bool>();
	// std::cout << "Test <bool, bool>			: ";				test_max_size<bool, bool>();
	// std::cout << "Test <short, short>		: ";				test_max_size<short, short>();
	// std::cout << "Test <char, char>			: ";				test_max_size<char, char>();
	std::cout << "Test <int, int>			: ";			test_max_size<int, int>();
	std::cout << "Test <float, float>		: ";			test_max_size<float, float>();
	std::cout << "Test <double, double>		: ";			test_max_size<double, double>();
	std::cout << "Test <std::string, std::string>		: ";		test_max_size<std::string, std::string>();
	std::cout << "Test <exampleClass, exampleClass>	: ";		test_max_size<exampleClass, exampleClass>();

	return (0);
}
