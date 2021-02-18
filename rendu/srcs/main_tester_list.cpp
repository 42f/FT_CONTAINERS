/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester_list.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:15 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 10:51:48 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_list.hpp"

int
main_tester_list( void )	{

	std::cout << std::endl << std::endl;
	std::cout << MAIN_TITLE << " CONTAINER TESTER =============> " << __func__ << "  " << RESET_COLOR << std::endl;

	try {

		test_list_instantiation();
		test_list_operatorEqual();

		test_list_iterator();
		test_list_reverseIterator();
		test_list_capacities();
		test_list_element_access();
		test_list_assign();
		test_list_push_back_push_front_pop_back_pop_front();
		test_list_insert_erase();
		test_list_member_swap();
		test_list_resize();
		test_list_clear();
		test_list_splice();
		test_list_remove();
		test_list_remove_if();
		test_list_unique();
		test_list_merge();
		test_list_sort();
		test_list_reverse();

		test_list_relational_operators();
		test_list_nonmember_swap();

		if (DEBUG_MODE == 0)
		{
			std::cout << SUBTITLE << "ALL TESTS PASSED ~~~~~~>  " << RESET_COLOR;
			testBool(1 == 1);
		}
	}
	catch ( failedTest & )	{
		std::cout << ERROR_TITLE << "SOME TEST FAILED !! \t \xE2\x9D\x8C" << RESET_COLOR << std::endl;
		return (1);
	}
	catch ( std::exception & e )	{
		std::cout << ERROR_TITLE << "Got exception: " << e.what() << RESET_COLOR << std::endl;
		return (1);
	}
	return (0);
}
