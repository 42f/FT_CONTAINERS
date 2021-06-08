/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:24 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/08 14:53:52 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Compilation may change DEBUG_MODE setting to
 *
 * 	DEBUG_MODE=0 -> no special output
 * 	DEBUG_MODE=1 -> continue after test a failed (abort otherwise)
 * 				 	+ minimal informations (mainly constructor/destructor calls)
 * 	DEBUG_MODE=2 -> more indepth infos
*/

# include "./tester/bvaletteTester_list.hpp"
# include "./tester/bvaletteTester_vector.hpp"
# include "./tester/bvaletteTester_map.hpp"

# include "./tester/bvaletteTester_deque.hpp"
# include "./tester/bvaletteTester_stack.hpp"
# include "./tester/bvaletteTester_queue.hpp"

int main ( void )	{

	try {
		main_tester_vector();
		main_tester_list();
		main_tester_map();
		main_tester_deque();
		main_tester_stack();
		main_tester_queue();

		{
			std::cout << SUBTITLE << " For ALL CONTAINERS, ALL TESTS PASSED ~~~~~~> " << RESET_COLOR;
			std::cout << BLINK << "\t \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x8A" << RESET_COLOR << std::endl;
			std::cout << BLINK << "                         " << "\t \xF0\x9F\x8E\x89 \xF0\x9F\x8E\x8A" << RESET_COLOR << std::endl;
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
