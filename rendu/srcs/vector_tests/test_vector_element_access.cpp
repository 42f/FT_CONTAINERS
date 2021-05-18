/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_element_access.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:54 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/18 09:50:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"

int
test_vector_element_access( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>	std_c0;
		size_t				testSize = 6;


		for (size_t i = 1; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
			testVector(ft_c0, std_c0, NOPRINT);
			std::cout << SUBTITLE << "Test front()" << RESET_COLOR << std::endl;
			testBool(ft_c0.front() == std_c0.front(), __LINE__);
			std::cout << SUBTITLE << "Test back()" << RESET_COLOR << std::endl;
			std::cout << "ft back = " << ft_c0.back() << " std back = " << std_c0.back() << std::endl;
			testBool(ft_c0.back() == std_c0.back(), __LINE__);
		}

		ft_c0.assign(1,42);
		std_c0.assign(1,42);
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "Test front()" << RESET_COLOR << std::endl;
		testBool(ft_c0.front() == std_c0.front(), __LINE__);
		std::cout << SUBTITLE << "Test back()" << RESET_COLOR << std::endl;
		testBool(ft_c0.back() == std_c0.back(), __LINE__);

		ft_c0.clear();
		std_c0.clear();
		testVector(ft_c0, std_c0, NOPRINT);
		std::cout << SUBTITLE << "Test front()" << RESET_COLOR << std::endl;
		testBool(ft_c0.front() == std_c0.front(), __LINE__);
		std::cout << SUBTITLE << "Test back()" << RESET_COLOR << std::endl;
		testBool(ft_c0.back() == std_c0.back(), __LINE__);


	}
	return (0);
}

