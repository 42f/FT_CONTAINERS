/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_insert_erase.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:19 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 08:31:45 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_insert_erase( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::vector<std::string>	ft_c0;
		std::vector<std::string>	std_c0;

		std::string	val("helloworld");

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ft_c0.insert(ft_c0.end(), 5, val);
		ft_c0.push_front("the Begining...");
		ft_c0.push_back("the End...");

		std_c0.insert(std_c0.end(), 5, val);
		std_c0.push_front("the Begining...");
		std_c0.push_back("the End...");

		testVector(ft_c0, std_c0, NOPRINT);

		ft::vector<std::string>	ft_c1;
		std::vector<std::string>	std_c1;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;
		ft_c1.insert(ft_c1.begin(), ft_c0.begin(), ft_c0.end());
		std_c1.insert(std_c1.begin(), std_c0.begin(), std_c0.end());

		testVector(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ Erase with erase(iterator) ]" << RESET_COLOR << std::endl;
		for (int i = 0; i < 3; i++)
		{
			std::cout << "return ft = " << &(*ft_c1.erase(--ft_c1.end())) << std::endl;
			std::cout << "return std= " << &(*std_c1.erase(--std_c1.end())) << std::endl;
		}

		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ Erase with erase(iterator, iterator) ]" << RESET_COLOR << std::endl;
		std::cout << "return ft  = " << &(*ft_c1.erase(ft_c1.begin(), --ft_c1.end())) << std::endl;
		std::cout << "return std = " << &(*std_c1.erase(std_c1.begin(), --std_c1.end())) << std::endl;

		testVector(ft_c1, std_c1, NOPRINT);
		ft_c1.erase(ft_c1.begin(), ft_c1.end());
		std_c1.erase(std_c1.begin(), std_c1.end());
		testVector(ft_c1, std_c1, NOPRINT);
	}
	return (0);
}
