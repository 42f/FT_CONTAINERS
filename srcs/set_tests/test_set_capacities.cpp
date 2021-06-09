/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_set_capacities.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 09:56:19 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/09 14:11:58 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <limits>
# include "./tester/exampleClass.hpp"
# include "./tester/bvaletteTester_set.hpp"

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };

		void m(void) 		{ std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const	{ std::cout << "foo::m const called [" << this->value << "]" << std::endl; };

		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};

		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}

	private:
		value_type	value;
		bool		_verbose;

};

template <typename T>
class bar {
	public:

		bar(void) {};
		~bar(void) {};

	private:
		T			value;
		bool		_verbose;

};

template < typename T, typename U>
void
test_max_size()	{
	size_t std_c0 = std::set<const T, U>().max_size();
	size_t ft_c0 = ft::set<const T, U>().max_size();
	std::cout << "Sizes returned : ft("<< ft_c0 <<") std("<< std_c0 <<")" << RESET_COLOR << std::endl;
	try {
		testBool(std_c0 == ft_c0, __LINE__);
	}
	catch (failedTest &e) {
		std::cout << ERROR_TITLE << "Sizes returned : ft("<< ft_c0/100000000000000 <<") std("<< std_c0/100000000000000 <<")" << RESET_COLOR << std::endl;
		throw failedTest();
	}
}

int
test_set_capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 5;

		std::cout << HEADER_TITLE << "[ Empty / size on empty set ]" << RESET_COLOR << std::endl;
		std::set<int>		std_c0;
		ft::set<int>		ft_c0;
		testBool(std_c0.empty() == ft_c0.empty(), __LINE__);
		testBool(std_c0.size() == ft_c0.size(), __LINE__);

		std::cout << HEADER_TITLE << "[ Empty / size on non empty set ]" << RESET_COLOR << std::endl;
		for(int i = 0; i < static_cast<int>(testSize); i++)	{
			std_c0.insert(i);
			ft_c0.insert(i);
			testBool(std_c0.empty() == ft_c0.empty(), __LINE__, i);
			testBool(std_c0.size() == ft_c0.size(), __LINE__, i);
		}
	}
	std::cout << HEADER_TITLE << "[ Max Size with various types ]" << RESET_COLOR << std::endl;

	std::cout << "Test <int, bar<bool> >		: " ;			test_max_size<int, bar<bool> >();
	std::cout << "Test <int, bar<double> >		: " ;			test_max_size<int, bar<double> >();
	std::cout << "Test <bar<unsigned int>, int >		: " ;			test_max_size<bar<unsigned int>, int>();
	std::cout << "Test <bar<int>, int >		: " ;			test_max_size<bar<int>, int>();
	std::cout << "Test <int, bar<int> >		: " ;			test_max_size<int, bar<int> >();
	std::cout << "Test <int, foo<bool> >		: " ;			test_max_size<int, foo<bool> >();
	std::cout << "Test <int, foo<double> >		: " ;			test_max_size<int, foo<double> >();
	std::cout << "Test <int, foo<int> >		: " ;			test_max_size<int, foo<int> >();
	std::cout << "Test <int, double>		: " ;			test_max_size<int, long>();
	std::cout << "Test <int, int>			: " ;			test_max_size<int, int>();
	std::cout << "Test <float, float>		: " ;			test_max_size<float, float>();
	std::cout << "Test <double, double>		: " ;			test_max_size<double, double>();
	std::cout << "Test <std::string, std::string>		: " ;	test_max_size<std::string, std::string>();
	std::cout << "Test <exampleClass, exampleClass>	: " ;		test_max_size<exampleClass, exampleClass>();
	std::cout << "Test <bool, int>		: " ;				test_max_size<bool, int>();
	std::cout << "Test <short, int>		: " ;				test_max_size<short, int>();
	std::cout << "Test <char, int>		: " ;				test_max_size<char, int>();
	std::cout << "Test <int, int>		: " ;				test_max_size<int, int>();
	std::cout << "Test <float, int>		: " ;				test_max_size<float, int>();
	std::cout << "Test <double, int>	: " ;				test_max_size<double, int>();
	std::cout << "Test <std::string, int>	: " ;		test_max_size<std::string, int>();
	std::cout << "Test <exampleClass, int>	: " ;		test_max_size<exampleClass, int>();
	std::cout << "Test <int, bool>			: " ;				test_max_size<int, bool>();
	std::cout << "Test <int, short>			: " ;				test_max_size<int, short>();
	std::cout << "Test <int, char>			: " ;				test_max_size<int, char>();
	std::cout << "Test <int, int>			: " ;				test_max_size<int, int>();
	std::cout << "Test <int, float>			: " ;				test_max_size<int, float>();
	std::cout << "Test <int, double>		: " ;				test_max_size<int, double>();
	std::cout << "Test <int, std::string>	: " ;		test_max_size<int, std::string>();
	std::cout << "Test <int, exampleClass>	: " ;		test_max_size<int, exampleClass>();


	// attention thrown exception is commented in test block !
	// -- requires node specialization
	// std::cout << "Test <bool, short>			: ";			test_max_size<bool, bool>();
	// std::cout << "Test <bool, bool>			: ";				test_max_size<bool, bool>();
	// std::cout << "Test <short, short>		: ";				test_max_size<short, short>();
	// std::cout << "Test <char, char>			: ";				test_max_size<char, char>();


	return (0);
}