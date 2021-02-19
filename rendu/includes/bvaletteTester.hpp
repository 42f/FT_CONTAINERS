#ifndef BVALETTETESTER_HPP
# define BVALETTETESTER_HPP

#include <list>
#include <vector>

#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>
#include <string>
#include <iostream>
#include <exception>

#include "bvaletteTester_defines.hpp"

class failedTest :  public std::exception {};

class exampleClass : public std::string	{

	public:

		std::string a;
		exampleClass( void ) : a("HelloWorld") {
			if (DEBUG_MODE >=3) std::cout << "Ctor exampleClass.." << std::endl;
		};

		exampleClass & operator=( exampleClass const & rhs )	{
			if (DEBUG_MODE >=3) std::cout << "Equal operator =" << std::endl;
			if ( this != &rhs )
			{
				this->a = rhs.a;
			}
			return *this;
		}
};

// std::ostream &			operator<<( std::ostream & o, exampleClass const & i )
// {
// 	o << i.a;
// 	return o;
// };

class ex{
public:

	int a;
	ex( void ) : a(21) {};

	ex & operator=( ex const & rhs )	{
		if ( this != &rhs )
		{
			this->a = rhs.a;
		}
		return *this;
	}

};

// std::ostream &			operator<<( std::ostream & o, ex const & i )
// {
// 	o << i.a;
// 	return o;
// }

bool	testBool(bool b, int const lineNo = -1 );

bool 	more_than_100 (const int& value);
bool 	more_than_10 (const int& value);
bool 	less_or_eq_10 (const int& value);
bool 	smaller_than ( int first, int second);
bool 	greater_than ( int first, int second);
bool 	same_integral_part (double first, double second);
// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

#endif
