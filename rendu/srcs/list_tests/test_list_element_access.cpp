/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_element_access.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:01:17 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/18 09:50:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_list.hpp"

int
test_list_element_access( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		size_t				testSize = 6;


		for (size_t i = 1; i < testSize; i++)	{
			ftl0.push_back(i);
			stdl0.push_back(i);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << HEADER_TITLE << "Test front() element access on list of size: "<< ftl0.size() << RESET_COLOR << std::endl;
		testBool(ftl0.front() == stdl0.front(), __LINE__);
		std::cout << HEADER_TITLE << "Test back() element access on list of size: "<< ftl0.size() << RESET_COLOR << std::endl;
		testBool(ftl0.back() == stdl0.back(), __LINE__);

		ft::list<int>		ftl1(1,42);
		std::list<int>		stdl1(1,42);
		std::cout << HEADER_TITLE << "Test front() element access on list of size: "<< ftl1.size() << RESET_COLOR << std::endl;
		testBool(ftl1.front() == stdl1.front(), __LINE__);
		std::cout << HEADER_TITLE << "Test back() element access on list of size: "<< ftl1.size() << RESET_COLOR << std::endl;
		testBool(ftl1.back() == stdl1.back(), __LINE__);
	}
	return (0);
}

