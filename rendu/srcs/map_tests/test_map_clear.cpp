/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_clear.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:49:36 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/22 14:25:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

int
test_map_clear( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with map of 1000000 floats" << RESET_COLOR << std::endl;
		ft::map<float> ft_c0 (1000000, 42.21f);
		std::map<float> std_c0 (1000000, 42.21f);

		testMap(ft_c0, std_c0, NOPRINT);
		ft_c0.clear();
		std_c0.clear();
		testMap(ft_c0, std_c0, NOPRINT);
	}
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with empty map" << RESET_COLOR << std::endl;
		ft::map<float> ft_c0;
		std::map<float> std_c0;

		testMap(ft_c0, std_c0, NOPRINT);
		ft_c0.clear();
		std_c0.clear();
		testMap(ft_c0, std_c0, NOPRINT);
	}
	return (0);
}
