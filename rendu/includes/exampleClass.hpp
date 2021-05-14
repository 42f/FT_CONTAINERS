#ifndef EXAMPLECLASS_HPP
# define EXAMPLECLASS_HPP

#include <iostream>
#include <string>
#include "bvaletteTester_defines.hpp"

class exampleClass : public std::string	{

	public:

		std::string a;
		int			b;
		exampleClass( void ) : a("HelloWorld"), b(rand()) {
			std::cout << "CONSTRUCTION OF EX, " << b << std::endl;
			if (DEBUG_MODE >=3) std::cout << "Ctor exampleClass.." << std::endl;
		};
		~exampleClass( void ) {
			if (DEBUG_MODE >=3) std::cout << "Dtor exampleClass.." << std::endl;
		};

		exampleClass & operator=( exampleClass const & rhs )	{
			if (DEBUG_MODE >=3) std::cout << "Equal operator =" << std::endl;
			if ( this != &rhs )
			{
				this->a = rhs.a;
			}
			return *this;
		}

		bool
		operator<( exampleClass& rhs )	{
			return (b < rhs.b);
		}
};

std::ostream&
operator<<( std::ostream & o, exampleClass const & i )	{
	o << i.b;
	return o;
};

#endif
