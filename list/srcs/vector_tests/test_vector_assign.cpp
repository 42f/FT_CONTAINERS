/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_assign.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:48:00 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 09:48:09 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester.hpp"

int
test_vector_assign( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0(3, -1);
		std::list<int>	stdl0(3, -1);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 5 with value 42 ]" << RESET_COLOR << std::endl;
		ftl0.assign(5, 42);
		stdl0.assign(5, 42);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 99 ]" << RESET_COLOR << std::endl;
		ftl0.assign(1, 99);
		stdl0.assign(1, 99);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 100 ]" << RESET_COLOR << std::endl;
		ftl0.assign(1, 100);
		stdl0.assign(1, 100);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign with Iterators from list containing 3 times value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl1(3, -1);
		std::list<int>	stdl1(3, -1);
		ftl1.push_front(42);
		stdl1.push_front(42);
		ftl1.push_back(99);
		stdl1.push_back(99);
		ftl0.assign(ftl1.begin(), ftl1.end());
		stdl0.assign(stdl1.begin(), stdl1.end());
		testList(ftl0, stdl0, NOPRINT);

	}
	return (0);
}
