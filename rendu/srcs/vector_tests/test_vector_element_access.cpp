/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_element_access.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:54 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 14:22:40 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_element_access( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ft_c0;
		std::list<int>		std_c0;
		size_t				testSize = 6;


		for (size_t i = 1; i < testSize; i++)	{
			ft_c0.push_back(i);
			std_c0.push_back(i);
		}
		testList(ft_c0, std_c0, NOPRINT);
		std::cout << HEADER_TITLE << "Test front() element access on list of size: "<< ft_c0.size() << RESET_COLOR << std::endl;
		testBool(ft_c0.front() == std_c0.front(), __LINE__);
		std::cout << HEADER_TITLE << "Test back() element access on list of size: "<< ft_c0.size() << RESET_COLOR << std::endl;
		testBool(ft_c0.back() == std_c0.back(), __LINE__);

		ft::list<int>		ft_c1(1,42);
		std::list<int>		std_c1(1,42);
		std::cout << HEADER_TITLE << "Test front() element access on list of size: "<< ft_c1.size() << RESET_COLOR << std::endl;
		testBool(ft_c1.front() == std_c1.front(), __LINE__);
		std::cout << HEADER_TITLE << "Test back() element access on list of size: "<< ft_c1.size() << RESET_COLOR << std::endl;
		testBool(ft_c1.back() == std_c1.back(), __LINE__);
	}
	return (0);
}

