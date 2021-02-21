/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester_vector.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:15 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 17:31:33 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
main_tester_vector( void )	{

	std::cout << std::endl << std::endl;
	std::cout << MAIN_TITLE << " CONTAINER TESTER ============= " << __func__ << " ||||||| " << RESET_COLOR << std::endl;

	try {

		// test_vector_capacities();
		// test_vector_resize();

		// test_vector_instantiation();
		// test_vector_operatorEqual();

		// test_vector_iterator();
		// test_vector_reverseIterator();
		// test_vector_element_access();
		// test_vector_assign();
		// test_vector_push_back_pop_back();
		test_vector_insert_erase();
		// test_vector_member_swap();
		// test_vector_clear();
		// test_vector_splice();
		// test_vector_remove();
		// test_vector_remove_if();
		// test_vector_unique();
		// test_vector_merge();
		// test_vector_sort();
		// test_vector_reverse();

		// test_vector_relational_operators();
		// test_vector_nonmember_swap();

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
