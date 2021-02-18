/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_clear.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:49:36 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 10:43:06 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_clear( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with list of 1000000 floats" << RESET_COLOR << std::endl;
		ft::list<float> ftl0 (1000000, 42.21f);
		std::list<float> stdl0 (1000000, 42.21f);

		testList(ftl0, stdl0, NOPRINT);
		ftl0.clear();
		stdl0.clear();
		testList(ftl0, stdl0, NOPRINT);
	}
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "TEST CLEAR FUNCTION with empty list" << RESET_COLOR << std::endl;
		ft::list<float> ftl0;
		std::list<float> stdl0;

		testList(ftl0, stdl0, NOPRINT);
		ftl0.clear();
		stdl0.clear();
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}
