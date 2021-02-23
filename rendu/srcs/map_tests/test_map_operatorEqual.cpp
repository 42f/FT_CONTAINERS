/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_operatorEqual.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:23 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:08:11 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_operatorEqual( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::map<std::string>	ft_c0(10, "hello");
		std::map<std::string>	std_c0(10, "hello");
		ft::map<std::string>	ft_c1(5, "byee");
		std::map<std::string>	std_c1(5, "byee");

		std::cout << SUBTITLE << "[ Instanciate map 0 with 10 \"hello\" and map 1 with 5 \"byeee\" ]" << RESET_COLOR << std::endl;
		testMap(ft_c0, std_c0, NOPRINT);
		testMap(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ map0=map1 ]" << RESET_COLOR << std::endl;

		ft_c0 = ft_c1;
		std_c0 = std_c1;

		testMap(ft_c0, std_c0, NOPRINT);
		testMap(ft_c1, std_c1, NOPRINT);
	}
	return (0);
}
