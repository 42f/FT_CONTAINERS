/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_clear.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:49:36 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 17:23:37 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_clear( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with vector of 1000000 floats" << RESET_COLOR << std::endl;
		ft::vector<float> ft_c0 (1000000, 42.21f);
		std::vector<float> std_c0 (1000000, 42.21f);

		testVector(ft_c0, std_c0, NOPRINT);
		ft_c0.clear();
		std_c0.clear();
		testVector(ft_c0, std_c0, NOPRINT);
	}
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with empty vector" << RESET_COLOR << std::endl;
		ft::vector<float> ft_c0;
		std::vector<float> std_c0;

		testVector(ft_c0, std_c0, NOPRINT);
		ft_c0.clear();
		std_c0.clear();
		testVector(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
