/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_sort.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:02:29 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/18 09:50:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_list.hpp"

int
test_list_sort( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "LIST FILLED WITH A RANDOM NUMBER OF RANDOM VALUES" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		srand(reinterpret_cast<long unsigned int>(&stdl0));
		size_t				testSize = rand() % 15000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 10000;
			ftl0.push_back(val);
			stdl0.push_back(val);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ sort list 0 with greater_than Compare ]" << RESET_COLOR << std::endl;
		ftl0.sort(greater_than);
		stdl0.sort(greater_than);
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ sort list 0 with not argument ]" << RESET_COLOR << std::endl;
		ftl0.sort();
		stdl0.sort();
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}

