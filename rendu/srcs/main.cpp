/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:24 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/24 09:43:20 by bvalette         ###   ########.fr       */
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

int main ( void )	{

	// main_tester_list();
	main_tester_vector();
	// main_tester_map();

	return (0);
}
