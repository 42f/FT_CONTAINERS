/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester_map.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:15 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/15 11:24:16 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
main_tester_map( void )	{

	std::cout << std::endl << std::endl;
	std::cout << MAIN_TITLE << " CONTAINER TESTER ============= " << __func__ << " ||||||| " << RESET_COLOR << std::endl;

	try {

		test_map_instantiation();
		test_map_insert_erase();
		test_map_capacities();
		test_map_iterator();

	/******* NOT TESTED ******
		test_map_reverseIterator();

		test_map_member_swap();

		test_map_clear();
		test_map_at_operatorBrackets();

		test_map_nonmember_swap();
		test_map_element_access();
		test_map_relational_operators();
		test_map_operatorEqual();
	*/
	/******* NOT USED ******

		test_map_resize();
		test_map_push_back_pop_back();
		test_map_assign();
		test_map_splice();
		test_map_remove();
		test_map_remove_if();
		test_map_unique();
		test_map_merge();
		test_map_sort();
		test_map_reverse();

	*/
		if (DEBUG_MODE == 0)
		{
			std::cout << SUBTITLE << "ALL TESTS PASSED ~~~~~~> " << RESET_COLOR;
			std::cout << BLINK << "\t \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x8A" << RESET_COLOR << std::endl;
			usleep(10);
			std::cout << BLINK << "                         " << "\t \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x8A" << RESET_COLOR << std::endl;
			usleep(10);
			std::cout << BLINK << "                         " << "\t \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x8A" << RESET_COLOR << std::endl;
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
