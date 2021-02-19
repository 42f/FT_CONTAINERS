/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_operatorEqual.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:23 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 14:22:40 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_operatorEqual( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<std::string>	ft_c0(10, "hello");
		std::list<std::string>	std_c0(10, "hello");
		ft::list<std::string>	ft_c1(5, "byee");
		std::list<std::string>	std_c1(5, "byee");

		std::cout << SUBTITLE << "[ Instanciate list 0 with 10 \"hello\" and list 1 with 5 \"byeee\" ]" << RESET_COLOR << std::endl;
		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ list0=list1 ]" << RESET_COLOR << std::endl;

		ft_c0 = ft_c1;
		std_c0 = std_c1;

		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);
	}
	return (0);
}
