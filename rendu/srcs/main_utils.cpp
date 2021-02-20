/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:23:24 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 10:45:38 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester.hpp"

bool more_than_100 (const int& value) { return (value>100); }
bool more_than_10 (const int& value) { return (value>10); }
bool less_or_eq_10 (const int& value) { return (value<=10); }
bool smaller_than ( int first, int second)	{ return ( first<second ); }
bool greater_than ( int first, int second)	{ return ( first>second ); }

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

bool	testBool(bool b, int const lineNo )	{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \t \342\234\205" << std::endl;
	else	{
		std::cout << ERROR_TITLE << "[ FAILURE at line..." << lineNo << "]" << RESET_COLOR << " \t \342\235\214" << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
	}
	return (b);
}