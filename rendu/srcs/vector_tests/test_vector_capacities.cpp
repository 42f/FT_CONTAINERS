/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_capacities.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:48:58 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/18 09:50:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"

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
		{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ max_size for a vector of " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::vector<bool>	std(testSize);
		ft::vector<bool>		ft(testSize);
		testBool(std.max_size() == ft.max_size(), __LINE__);
		std::cout << "bool : max_size for std : " << std.max_size() << std::endl;
		std::cout << "bool : max_size for ft  : " << ft.max_size() << std::endl;

	}
	{
		std::vector<char>		std_c0;
		ft::vector<char>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "char : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "char : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::vector<std::string>		std_c0;
		ft::vector<std::string>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "std::string : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "std::string : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::vector<float>		std_c0;
		ft::vector<float>		ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "float : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "float : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::vector<int>		std_c0;
		ft::vector<int>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "int : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "int : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::vector<short>		std_c0;
		ft::vector<short>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "short : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "short : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}
	{
		std::vector<double>		std_c0;
		ft::vector<double>			ft_c0;
		testBool(std_c0.max_size() == ft_c0.max_size(), __LINE__);
		std::cout << "double : MAX SIZE = std. " << std_c0.max_size() << std::endl;
		std::cout << "double : MAX SIZE = ft . " << ft_c0.max_size() << std::endl;
	}

	return (0);
}
