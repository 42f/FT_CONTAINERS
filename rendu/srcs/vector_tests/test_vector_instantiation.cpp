/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_instantiation.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:31 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 11:16:16 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_instantiation( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << TITLE << "~~~~ To see constructor calls, compile with " << RESET_COLOR << "-> make debug_mode=1 re f "<< std::endl;
	{
		std::cout << SUBTITLE << "[ DEFAULT CONSTRUCTOR ]" << RESET_COLOR << std::endl;
		{
			ft::vector<std::string>	ftl0;
			std::vector<std::string>	stdl0;
			testVector(ftl0, stdl0, NOPRINT);
			ft::vector<float>		ftl1;
			std::vector<float>	stdl1;
			testVector(ftl1, stdl1, NOPRINT);
		}
		// std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>	ftl0(5, 123);
		// 	std::vector<int>	stdl0(5, 123);
		// 	testList(ftl0, stdl0, NOPRINT);
		// }
		// std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value explicitly casted ]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>	ftl0(static_cast<size_t>(5),123);
		// 	std::vector<int>	stdl0(static_cast<size_t>(5),123);
		// 	testList(ftl0, stdl0, NOPRINT);
		// }
		// std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value ]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>	ftl0(5);
		// 	std::vector<int>	stdl0(5);
		// 	testList(ftl0, stdl0, NOPRINT);
		// }
		// std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value and with classExample which has a default value ]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<exampleClass>	ftl0(5);
		// 	std::vector<exampleClass>	stdl0(5);
		// 	testList(ftl0, stdl0, NOPRINT);
		// }
		// std::cout << SUBTITLE << "[ RANGE CONSTRUCTOR test: list0 with fill and list1 with range ctor from list0 iterators ]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>	ftl0(5, 123);
		// 	std::vector<int>	stdl0(5, 123);
		// 	std::cout << SUBTITLE << "->>\t\t[ RANGE CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		// 	ft::vector<int>	ftl1(ftl0.begin(), ++ftl0.begin());
		// 	std::vector<int>	stdl1(stdl0.begin(), ++stdl0.begin());
		// 	testList(ftl0, stdl0, NOPRINT);
		// 	testList(ftl1, stdl1, NOPRINT);

		// }
		// std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with 5 elements]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>		ftl0(5, 123);
		// 	std::vector<int>		stdl0(5, 123);

		// 	ft::vector<int>		ftl1(ftl0);
		// 	std::vector<int>		stdl1(stdl0);
		// 	testList(ftl0, stdl0, NOPRINT);
		// 	testList(ftl1, stdl1, NOPRINT);
		// 	std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
		// 	testBool(&(*ftl0.begin()) != &(*ftl1.begin()), __LINE__);
		// 	testBool(&(*stdl0.begin()) != &(*stdl1.begin()), __LINE__);
		// }
		// std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with no elements]" << RESET_COLOR << std::endl;
		// {
		// 	ft::vector<int>		ftl0;
		// 	std::vector<int>		stdl0;

		// 	ft::vector<int>		ftl1(ftl0);
		// 	std::vector<int>		stdl1(stdl0);
		// 	testList(ftl0, stdl0, NOPRINT);
		// 	testList(ftl1, stdl1, NOPRINT);

		// 	std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
		// 	testBool(&(*ftl0.begin()) != &(*ftl1.begin()), __LINE__);
		// 	testBool(&(*stdl0.begin()) != &(*stdl1.begin()), __LINE__);
		// }
	}
	return (0);
}
