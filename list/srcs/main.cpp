/**
 * Compilation may change DEBUG_MODE setting to
 *
 * 	DEBUG_MODE=0 -> no special output
 * 	DEBUG_MODE=1 -> continue after test a failed (abort otherwise)
 * 				 	+ minimal informations (mainly constructor/destructor calls)
 * 	DEBUG_MODE=2 -> more indepth infos
*/


#include "list.hpp"

#include <math.h>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
// #include <type_traits>
#include <list>
#include <unistd.h>
#include <signal.h>
#include <execinfo.h>

#ifndef RESET_COLOR
# define RESET_COLOR   "\033[0m"
#endif

#ifndef TITLE
# define TITLE    "\n\033[31m\033[7m"
#endif

#ifndef ERROR_TITLE
# define ERROR_TITLE    "\n\033[41m\033[5m\t"
#endif

#ifndef ERROR_SOURCE
# define ERROR_SOURCE    "\n\033[5m\033[041m"
#endif

#ifndef SUBTITLE
# define SUBTITLE    "\n\033[7m"
#endif

#ifndef HEADER_TITLE
# define HEADER_TITLE    "\n   \xF0\x9F\x86\x95 \033[43m\033[30m "
#endif

#ifndef PRINT_TITLE
# define PRINT_TITLE    "\n\033[43m\t"
#endif

#ifndef PRINT_STD_TITLE
# define PRINT_STD_TITLE    "\n\033[44m\t"
#endif

#ifndef TESTOK_TITLE
# define TESTOK_TITLE    "\n\033[102m\t"
#endif

#ifndef PRINT
# define PRINT		true
#endif

#ifndef PRINT
# define NOPRINT	false
#endif

class failedTest :  public std::exception {};

class exampleClass : public std::string{

	public:

		std::string a;
		exampleClass( void ) : a("HelloWorld") {};

		exampleClass & operator=( exampleClass const & rhs )	{
			if ( this != &rhs )
			{
				this->a = rhs.a;
			}
			return *this;
		}
		// exampleClass & operator*( exampleClass const & rhs )	{
		// 	if ( this != &rhs )
		// 	{
		// 		this->a = rhs.a;
		// 	}
		// 	return *this;
		// }

};

std::ostream &			operator<<( std::ostream & o, exampleClass const & i )
{
	o << i.a;
	return o;
}

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

std::ostream &			operator<<( std::ostream & o, ex const & i )
{
	o << i.a;
	return o;
}

template< typename T>
void
putList( ft::list<T> const & lst, int errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ FT::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of list ]" << RESET_COLOR << " -> ";
	std::cout << lst.size() << std::endl;
	typename ft::list<T>::iterator it = lst.begin();
	typename ft::list<T>::iterator ite = lst.end();

	int	printMax;

	// if (errorPos == -1 && lst.size() > 100)
	if (lst.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(lst.size());
	for (int i = 0; lst.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(lst.size()))
			std::cout << ERROR_SOURCE << "ft: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "ft: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(lst.size()))
		std::cout << " !!\t List size is too large to print... stoping here." << std::endl;
}

template< typename T>
void
putList( std::list<T> const & lst, int errorPos = -1 )	{

	std::cout << PRINT_STD_TITLE << "[ STD::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_STD_TITLE << "[ size of list ]" << RESET_COLOR << " -> ";
	std::cout << lst.size() << std::endl;
	typename std::list<T>::const_iterator it = lst.begin();
	typename std::list<T>::const_iterator ite = lst.end();

	int	printMax;

	// if (errorPos == -1 && lst.size() > 100)
	if (lst.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(lst.size());
	for (int i = 0; lst.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(lst.size()))
			std::cout << ERROR_SOURCE << "std: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "std: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(lst.size()))
		std::cout << " !!\t List size is too large to print... stoping here." << std::endl;
}

bool	testBool(bool b, int const lineNo = -1 )	{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \t \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "[ FAILURE at line..." << lineNo << "]" << RESET_COLOR << " \t \342\235\214" << std::endl;
	return (b);
}

template< typename T>
void
testList( ft::list<T> const & ft_lst, std::list<T> const &std_lst, bool print, std::string message = "" )	{

	bool	success = true;

	if (message.empty() == false)
		std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	if (print == true)
	{
		putList<T>(std_lst);
		putList<T>(ft_lst);
	}

	if(ft_lst.size() != std_lst.size())	{
		if (print == false && success == true)
		{
			putList<T>(std_lst);
			putList<T>(ft_lst);
		}
		std::cout << TITLE <<"size: ft (" << ft_lst.size() << ") std (" << std_lst.size() << ") Diff ! " << RESET_COLOR << std::endl;
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
			//abort();
		else
			success = false;
	}

	if (ft_lst.size() > 0)
	{
		int i = 0;
		typename ft::list<T>::iterator	ft_it = ft_lst.begin();
		typename ft::list<T>::iterator	ft_ite = ft_lst.end();

		typename std::list<T>::const_iterator	std_it = std_lst.begin();
		typename std::list<T>::const_iterator	std_ite = std_lst.end();
		while (ft_it != ft_ite && std_it != std_ite)	{

			if(*ft_it != *std_it)	{
				if (print == false && success == true)
				{
					putList<T>(ft_lst, i);
					putList<T>(std_lst, i);
				}
				std::cout << TITLE <<"iterator at pos " << i << ": ft (" << *ft_it << ") " << RESET_COLOR;
				std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
				std::cout << "std (" << *std_it << ") Diff ! " << RESET_COLOR << std::endl;
				if (DEBUG_MODE < 1)
					throw failedTest();
					//abort();
				else
					success = false;
			}
			i++;
			ft_it++;
			std_it++;
		}
		if (ft_it != ft_ite || std_it != std_ite)	{
			if (print == false && success == true)
			{
				putList<T>(ft_lst);
				putList<T>(std_lst);
			}
			std::cout << TITLE <<"Diff in list after iterating thought it." << RESET_COLOR << std::endl;
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
			if (DEBUG_MODE < 1)
				throw failedTest();
				//abort();
			else
				success = false;
		}
	}
	if (print == true && success == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ] list sizes: ft(" << ft_lst.size() <<") std(" << std_lst.size() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	else if (success == true)
		std::cout << "[ TEST PASSED: no diff ] list sizes: ft(" << ft_lst.size() <<") std(" << std_lst.size() << ") \t \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "TEST FAILED !" << RESET_COLOR << std::endl;
}

void
handler(int sig) {
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

	std::cout << TITLE << "ASSERT WAS WRONG... so on test failed." << __func__ << RESET_COLOR << std::endl;
  // print out all the frames to stderr
  fprintf(stderr, "\n\nError: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

int
test_Capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		assert(testBool(std.empty() == ft.empty()));
	}
	{
		size_t		testSize = 5;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "Size of std : " << std.size() << std::endl;
		std::cout << "Size of ft  : " << ft.size() << std::endl;

		assert(testBool(std.size() == ft.size()));

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		assert(testBool(std.empty() == ft.empty()));
	}
	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ max_size for a list of " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<float>	std(testSize);
		ft::list<float>		ft(testSize);
		std::cout << "max_size for std : " << std.max_size() << std::endl;
		std::cout << "max_size for ft  : " << ft.max_size() << std::endl;
		assert(testBool(std.max_size() == ft.max_size()));

	}
	return (0);
}

int
test_operatorEqual( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<std::string>	ftl0(10, "hello");
		std::list<std::string>	stdl0(10, "hello");
		ft::list<std::string>	ftl1(5, "byee");
		std::list<std::string>	stdl1(5, "byee");

		std::cout << SUBTITLE << "[ Instanciate list 0 with 10 \"hello\" and list 1 with 5 \"byeee\" ]" << RESET_COLOR << std::endl;
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);

		std::cout << SUBTITLE << "[ list0=list1 ]" << RESET_COLOR << std::endl;

		ftl0 = ftl1;
		stdl0 = stdl1;

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	return (0);
}

int
test_push_back_push_front_pop_back_pop_front( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<std::string>	ftl0;
		std::list<std::string>	stdl0;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ftl0.push_front("the Begining...");
		ftl0.push_back("the End...");
		ftl0.push_back("the End...");

		stdl0.push_front("the Begining...");
		stdl0.push_back("the End...");
		stdl0.push_back("the End...");

		testList(ftl0, stdl0, NOPRINT);

		ftl0.pop_front();
		ftl0.pop_back();

		stdl0.pop_front();
		stdl0.pop_back();

		testList(ftl0, stdl0, NOPRINT);
		ftl0.pop_front();

		stdl0.pop_front();

		testList(ftl0, stdl0, NOPRINT);

	}
	return (0);
}
int
test_instantiation( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << TITLE << "~~~~ To see constructor calls, compile with " << RESET_COLOR << "-> make debug_mode=1 re f "<< std::endl;
	{
		std::cout << SUBTITLE << "[ DEFAULT CONSTRUCTOR ]" << RESET_COLOR << std::endl;
		{
			ft::list<std::string>	ftl0;
			std::list<std::string>	stdl0;
			testList(ftl0, stdl0, NOPRINT);
			ft::list<float>		ftl1;
			std::list<float>	stdl1;
			testList(ftl1, stdl1, NOPRINT);
		}

		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		{
			ft::list<int>	ftl0(5, 123);
			std::list<int>	stdl0(5, 123);
			testList(ftl0, stdl0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value explicitly casted ]" << RESET_COLOR << std::endl;
		{
			ft::list<int>	ftl0(static_cast<size_t>(5),123);
			std::list<int>	stdl0(static_cast<size_t>(5),123);
			testList(ftl0, stdl0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value ]" << RESET_COLOR << std::endl;
		{
			ft::list<int>	ftl0(5);
			std::list<int>	stdl0(5);
			testList(ftl0, stdl0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value and with classExample which has a default value ]" << RESET_COLOR << std::endl;
		{
			ft::list<exampleClass>	ftl0(5);
			std::list<exampleClass>	stdl0(5);
			testList(ftl0, stdl0, NOPRINT);
		}


		std::cout << SUBTITLE << "[ RANGE CONSTRUCTOR test: list0 with fill and list1 with range ctor from list0 iterators ]" << RESET_COLOR << std::endl;
		{
			ft::list<int>	ftl0(5, 123);
			std::list<int>	stdl0(5, 123);
			std::cout << SUBTITLE << "->>\t\t[ RANGE CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
			ft::list<int>	ftl1(ftl0.begin(), ++ftl0.begin());
			std::list<int>	stdl1(stdl0.begin(), ++stdl0.begin());
			testList(ftl0, stdl0, NOPRINT);
			testList(ftl1, stdl1, NOPRINT);

		}



		// std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with 5 elements]" << RESET_COLOR << std::endl;
		// {
		// 	ft::list<int>		ftl0(5, 123);
		// 	std::list<int>		stdl0(5, 123);

		// 	ft::list<int>		ftl1(ftl0);
		// 	std::list<int>		stdl1(stdl0);
		// 	testList(ftl0, stdl0, NOPRINT);
		// 	testList(ftl1, stdl1, NOPRINT);
		// 	std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
		// 	testBool(&(*ftl0.begin()) != &(*ftl1.begin()), __LINE__);
		// 	testBool(&(*stdl0.begin()) != &(*stdl1.begin()), __LINE__);
		// }
		// std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from list with no elements]" << RESET_COLOR << std::endl;
		// {
		// 	ft::list<int>		ftl0;
		// 	std::list<int>		stdl0;

		// 	ft::list<int>		ftl1(ftl0);
		// 	std::list<int>		stdl1(stdl0);
		// 	testList(ftl0, stdl0, NOPRINT);
		// 	testList(ftl1, stdl1, NOPRINT);

		// 	std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
		// 	testBool(&(*ftl0.begin()) != &(*ftl1.begin()), __LINE__);
		// 	testBool(&(*stdl0.begin()) != &(*stdl1.begin()), __LINE__);
		// }


		/**
		 * @brief -> for iterator tester
		*/
			// std::list<float>			stdl0;
			// std::list<float>::iterator	it_stdl0 = stdl0.begin();
			// std::list<float>::iterator	ite_stdl0 = stdl0.end();
			// if (it_stdl0 == ite_stdl0)
			// 	std::cout << "EQUAL" << std::endl;
			// else
			// 	std::cout << "NOT EQUAL" << std::endl;
			// ft::list<float>			ftl0;
			// ft::list<float>::iterator	it_ftl0 = ftl0.begin();
			// ft::list<float>::iterator	ite_ftl0 = ftl0.end();
			// if (it_ftl0 == ite_ftl0)
			// 	std::cout << "EQUAL" << std::endl;
			// else
			// 	std::cout << "NOT EQUAL" << std::endl;

	}
	return (0);
}

int
test_reverseIterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER VALUES" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			ftl0.push_back(i);
			stdl0.push_back(i);
		}
		testList(ftl0, stdl0, NOPRINT);

		ft::list<int>::reverse_iterator		ft_it = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_it2 = ftl0.rbegin();
		ft::list<int>::reverse_iterator		ft_itend = ftl0.rend();

		std::list<int>::reverse_iterator		std_it = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_it2 = stdl0.rbegin();
		std::list<int>::reverse_iterator		std_itend = stdl0.rend();

		std::cout << SUBTITLE << "[ test operator!= ]" << RESET_COLOR << std::endl;
		testBool(ft_it != ft_itend && std_it != std_itend, __LINE__);
		std::cout << SUBTITLE << "[ test operator== ]" << RESET_COLOR << std::endl;
		testBool(ft_it == ft_it2 && std_it == std_it2, __LINE__);
		std::cout << SUBTITLE << "[ test operator< ]" << RESET_COLOR << std::endl;
		testBool(ft_it < ft_itend , __LINE__);

/*
/usr/bin/../lib/gcc/x86_64-linux-gnu/7.5.0/../../../../include/c++/7.5.0/bits/stl_iterator.h:310:25:

error: invalid operands to binary expression
      ('std::reverse_iterator<std::_List_iterator<int> >::iterator_type' (aka 'std::_List_iterator<int>')
	   'std::reverse_iterator<std::_List_iterator<int> >::iterator_type')
    { return __y.base() < __x.base(); }
*/
		// std::cout << SUBTITLE << "[ loop test iterator decrement (rend()--) ]" << RESET_COLOR << std::endl;
		// for (size_t i = 0; i < ftl0.size(); i++)
		// {
		// 	std::cout << "itend = " << *ft_itend << std::endl;
		// 	testBool(*ft_itend == static_cast<int>(i), __LINE__);
		// 	ft_itend--;
		// }
		// std::cout << SUBTITLE << "[ test operator= ]" << RESET_COLOR << std::endl;
		// ft_it2 = ft_it;
		// testBool(ft_it == ft_it2, __LINE__);
		// std::cout << SUBTITLE << "[ loop test iterator decrement (rbegin()++) ]" << RESET_COLOR << std::endl;
		// putList(ftl0);
		// ft_it = ftl0.rbegin();
		// for (size_t i = 0; i < ftl0.size(); i++)
		// {
		// 	std::cout << "it = " << *ft_it << std::endl;
		// 	testBool(*ft_it == static_cast<int>(i), __LINE__);
		// 	ft_it++;
		// }
		// testBool(static_cast<size_t>(ft_itend - ft_it) == ftl0.size(), __LINE__);
	// }
	// std::cout << HEADER_TITLE << "TEST ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	// {
	// 	ft::list<int>			l;
	// 	l.push_back(0);
	// 	l.push_back(1);
	// 	l.push_back(2);
	// 	l.push_back(3);
	// 	l.push_back(4);
	// 	l.push_back(5);
	// 	ft::list<int>::iterator it1 = ++l.begin();
	// 	ft::list<int>::iterator it2 = l.begin() + 2;
	// 	it1++;
	// 	ft::list<int>::iterator ite1 = --l.end();
	// 	ite1--;
	// 	ft::list<int>::iterator ite2 = l.end() - 2;

	// 	testBool(*it1 == 2, __LINE__);
	// 	testBool(*ite1 == 4, __LINE__);
	// 	testBool(*it1 == *it2, __LINE__);
	// 	testBool(*ite1 == *ite2, __LINE__);
	}
	return (0);
}

int
test_clear( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with floats ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<float> ftl0 (10, 42.21f);
		std::list<float> stdl0 (10, 42.21f);

		testList(ftl0, stdl0, NOPRINT);
		ftl0.clear();
		stdl0.clear();
		testList(ftl0, stdl0, NOPRINT);


	}
	return (0);
}

int
test_insert_erase( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<std::string>	ftl0;
		std::list<std::string>	stdl0;

		std::string	val("helloworld");

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ftl0.insert(ftl0.end(), 5, val);
		ftl0.push_front("the Begining...");
		ftl0.push_back("the End...");

		stdl0.insert(stdl0.end(), 5, val);
		stdl0.push_front("the Begining...");
		stdl0.push_back("the End...");

		testList(ftl0, stdl0, NOPRINT);

		ft::list<std::string>	ftl1;
		std::list<std::string>	stdl1;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;
		ftl1.insert(ftl1.begin(), ftl0.begin(), ftl0.end());
		stdl1.insert(stdl1.begin(), stdl0.begin(), stdl0.end());

		testList(ftl1, stdl1, NOPRINT);

		std::cout << SUBTITLE << "[ Erase with erase(iterator) ]" << RESET_COLOR << std::endl;
		for (int i = 0; i < 3; i++)
		{
			std::cout << "return ft = " << &(*ftl1.erase(--ftl1.end())) << std::endl;
			std::cout << "return std= " << &(*stdl1.erase(--stdl1.end())) << std::endl;
		}

		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ Erase with erase(iterator, iterator) ]" << RESET_COLOR << std::endl;
		std::cout << "return ft  = " << &(*ftl1.erase(ftl1.begin(), --ftl1.end())) << std::endl;
		std::cout << "return std = " << &(*stdl1.erase(stdl1.begin(), --stdl1.end())) << std::endl;

		testList(ftl1, stdl1, NOPRINT);
		ftl1.erase(ftl1.begin(), ftl1.end());
		stdl1.erase(stdl1.begin(), stdl1.end());
		testList(ftl1, stdl1, NOPRINT);


	}
	return (0);
}

int
test_resize( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list of 3 elements with no value ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0(3);
		std::list<int>	stdl0(3);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 5 with no value ]" << RESET_COLOR << std::endl;
		ftl0.resize(5);
		stdl0.resize(5);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 7 with value 42 ]" << RESET_COLOR << std::endl;
		ftl0.resize(7, 42);
		stdl0.resize(7, 42);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 999 and push front 111 ]" << RESET_COLOR << std::endl;
		ftl0.push_back(999);
		stdl0.push_back(999);
		ftl0.push_front(111);
		stdl0.push_front(111);
		std::cout << SUBTITLE << "[ resize to 3 with value 42 ]" << RESET_COLOR << std::endl;
		ftl0.resize(3, 42);
		stdl0.resize(3, 42);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 4 with value 42 ]" << RESET_COLOR << std::endl;
		ftl0.resize(4, 42);
		stdl0.resize(4, 42);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 4 with value 99 ]" << RESET_COLOR << std::endl;
		ftl0.resize(4, 99);
		stdl0.resize(4, 99);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ resize to 0 with no value ]" << RESET_COLOR << std::endl;
		ftl0.resize(0);
		stdl0.resize(0);
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}


int
test_nonmember_swap( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list0 of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0(3, -1);
		std::list<int>	stdl0(3, -1);
		testList(ftl0, stdl0, NOPRINT);


		std::cout << SUBTITLE << "[ Instanciate list1 of 3 elements value 42 + push front 0 + push back 99 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl1(3, 42);
		std::list<int>	stdl1(3, 42);
		ftl1.push_front(0);
		stdl1.push_front(0);
		ftl1.push_back(99);
		stdl1.push_back(99);
		testList(ftl1, stdl1, NOPRINT);

		ft::list<int>::iterator		ft_it0 = ftl0.begin();
		ft::list<int>::iterator		ft_it1 = ftl1.begin();
		std::list<int>::iterator	std_it0 = stdl0.begin();
		std::list<int>::iterator	std_it1 = stdl1.begin();

		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ft::swap(ftl0, ftl1);
		std::swap(stdl0, stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");

		std::cout << SUBTITLE << "[ test if iterator stayed valid while pointing to new values ]" << RESET_COLOR << std::endl;
		testBool(&(*ft_it0) == &(*ftl1.begin()), __LINE__);
		testBool(&(*ft_it1) == &(*ftl0.begin()), __LINE__);
		testBool(&(*std_it0) == &(*stdl1.begin()), __LINE__);
		testBool(&(*std_it1) == &(*stdl0.begin()), __LINE__);

		std::cout << SUBTITLE << "[ assign list 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ftl1.assign(10, 99);
		stdl1.assign(10, 99);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ft::swap(ftl0, ftl1);
		std::swap(stdl0, stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");


		std::cout << SUBTITLE << "[ assign list 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ftl1.assign(10, 99);
		stdl1.assign(10, 99);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ft::swap(ftl0, ftl1);
		std::swap(stdl0, stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");

		std::cout << SUBTITLE << "[ clear list0 ]" << RESET_COLOR << std::endl;
		ftl0.clear();
		stdl0.clear();
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ft::swap(ftl0, ftl1);
		std::swap(stdl0, stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");


	}
	return (0);
}
int
test_member_swap( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list0 of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0(3, -1);
		std::list<int>	stdl0(3, -1);
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ Instanciate list1 of 3 elements value 42 + push front 0 + push back 99 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl1(3, 42);
		std::list<int>	stdl1(3, 42);
		ftl1.push_front(0);
		stdl1.push_front(0);
		ftl1.push_back(99);
		stdl1.push_back(99);
		testList(ftl1, stdl1, NOPRINT);

		std::cout << SUBTITLE << "[ instanciate iterator to begin of list 0 and list 1 ]" << RESET_COLOR << std::endl;

		ft::list<int>::iterator		ft_it0 = ftl0.begin();
		ft::list<int>::iterator		ft_it1 = ftl1.begin();
		std::list<int>::iterator	std_it0 = stdl0.begin();
		std::list<int>::iterator	std_it1 = stdl1.begin();

		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ftl0.swap(ftl1);
		stdl0.swap(stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");

		std::cout << SUBTITLE << "[ test if iterator stayed valid while pointing to new values ]" << RESET_COLOR << std::endl;
		testBool(&(*ft_it0) == &(*ftl1.begin()), __LINE__);
		testBool(&(*ft_it1) == &(*ftl0.begin()), __LINE__);
		testBool(&(*std_it0) == &(*stdl1.begin()), __LINE__);
		testBool(&(*std_it1) == &(*stdl0.begin()), __LINE__);

		std::cout << SUBTITLE << "[ assign list 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ftl1.assign(10, 99);
		stdl1.assign(10, 99);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ftl0.swap(ftl1);
		stdl0.swap(stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");


		std::cout << SUBTITLE << "[ assign list 1 with 10 value 99 ]" << RESET_COLOR << std::endl;
		ftl1.assign(10, 99);
		stdl1.assign(10, 99);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ftl0.swap(ftl1);
		stdl0.swap(stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");

		std::cout << SUBTITLE << "[ clear list0 ]" << RESET_COLOR << std::endl;
		ftl0.clear();
		stdl0.clear();
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ swap 2 lists ]" << RESET_COLOR << std::endl;
		ftl0.swap(ftl1);
		stdl0.swap(stdl1);
		testList(ftl0, stdl0, NOPRINT, "Test list0");
		testList(ftl1, stdl1, NOPRINT, "Test list1");
	}
	return (0);
}
int
test_assign( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate list of 3 elements value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0(3, -1);
		std::list<int>	stdl0(3, -1);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 5 with value 42 ]" << RESET_COLOR << std::endl;
		ftl0.assign(5, 42);
		stdl0.assign(5, 42);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 99 ]" << RESET_COLOR << std::endl;
		ftl0.assign(1, 99);
		stdl0.assign(1, 99);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign 1 with value 100 ]" << RESET_COLOR << std::endl;
		ftl0.assign(1, 100);
		stdl0.assign(1, 100);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ assign with Iterators from list containing 3 times value -1 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl1(3, -1);
		std::list<int>	stdl1(3, -1);
		ftl1.push_front(42);
		stdl1.push_front(42);
		ftl1.push_back(99);
		stdl1.push_back(99);
		ftl0.assign(ftl1.begin(), ftl1.end());
		stdl0.assign(stdl1.begin(), stdl1.end());
		testList(ftl0, stdl0, NOPRINT);

	}
	return (0);
}

int
test_relational_operators( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with int ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Preliminary test on parameters ]" << RESET_COLOR << std::endl;

		std::list<float> std_a;
		std_a.push_back(10);
		std_a.push_back(20);
		std_a.push_back(30);
		std::list<float> std_b;
		std_b.push_back(10.42f);
		std_b.push_back(20);
		std_b.push_back(30.33f);

		testBool(std_a != std_b, __LINE__);

		std::cout << SUBTITLE << "[ Same values, same calls for ft ]" << RESET_COLOR << std::endl;

		ft::list<float> ft_a;
		ft_a.push_back(10);
		ft_a.push_back(20);
		ft_a.push_back(30);
		ft::list<float> ft_b;
		ft_b.push_back(10.42f);
		ft_b.push_back(20);
		ft_b.push_back(30.33f);

		testBool(ft_a != ft_b, __LINE__);
	}
	{
		std::cout << SUBTITLE << "[ Batch 1: All relational called for std ]" << RESET_COLOR << std::endl;
		std::list<int> std_a;
		std_a.push_back(10);
		std_a.push_back(20);
		std_a.push_back(30);
		std::list<int> std_b;
		std_b.push_back(10);
		std_b.push_back(20);
		std_b.push_back(30);
		std::list<int> std_c;
		std_c.push_back(30);
		std_c.push_back(20);
		std_c.push_back(10);

		testBool(std_a == std_b, __LINE__);
		testBool(std_b != std_c, __LINE__);
		testBool(std_b < std_c, __LINE__);
		testBool(std_c > std_b, __LINE__);
		testBool(std_a <= std_b, __LINE__);
		testBool(std_a >= std_b, __LINE__);

		std::cout << SUBTITLE << "[ Same values, same calls for ft ]" << RESET_COLOR << std::endl;

		ft::list<int> ft_a;
		ft_a.push_back(10);
		ft_a.push_back(20);
		ft_a.push_back(30);
		ft::list<int> ft_b;
		ft_b.push_back(10);
		ft_b.push_back(20);
		ft_b.push_back(30);
		ft::list<int> ft_c;
		ft_c.push_back(30);
		ft_c.push_back(20);
		ft_c.push_back(10);

		testBool(ft_a == ft_b, __LINE__);
		testBool(ft_b != ft_c, __LINE__);
		testBool(ft_b < ft_c, __LINE__);
		testBool(ft_c > ft_b, __LINE__);
		testBool(ft_a <= ft_b, __LINE__);
		testBool(ft_a >= ft_b, __LINE__);
	}
	{
		std::cout << SUBTITLE << "[ Batch 2: All relational called for std ]" << RESET_COLOR << std::endl;
		std::list<int> std_a;
		std_a.push_back(10);
		std_a.push_back(20);
		std_a.push_back(30);
		std::list<int> std_b;
		std_b.push_back(10);
		std_b.push_back(20);
		std_b.push_back(20);
		std_b.push_back(30);
		std::list<int> std_c;
		std_c.push_back(30);
		std_c.push_back(20);
		std_c.push_back(10);

		testBool(!(std_a == std_b), __LINE__);
		testBool(std_b != std_c, __LINE__);
		testBool(std_b < std_c, __LINE__);
		testBool(std_c > std_b, __LINE__);
		testBool(!(std_a <= std_b), __LINE__);
		testBool(std_a >= std_b, __LINE__);

		std::cout << SUBTITLE << "[ Same values, same calls for ft ]" << RESET_COLOR << std::endl;

		ft::list<int> ft_a;
		ft_a.push_back(10);
		ft_a.push_back(20);
		ft_a.push_back(30);
		ft::list<int> ft_b;
		ft_b.push_back(10);
		ft_b.push_back(20);
		ft_b.push_back(20);
		ft_b.push_back(30);
		ft::list<int> ft_c;
		ft_c.push_back(30);
		ft_c.push_back(20);
		ft_c.push_back(10);

		testBool(!(ft_a == ft_b), __LINE__);
		testBool(ft_b != ft_c, __LINE__);
		testBool(ft_b < ft_c, __LINE__);
		testBool(ft_c > ft_b, __LINE__);
		testBool(!(ft_a <= ft_b), __LINE__);
		testBool(ft_a >= ft_b, __LINE__);
	}
	{
		std::cout << SUBTITLE << "[ Batch 3: All relational called for std ]" << RESET_COLOR << std::endl;
		std::list<int> std_a;
		std_a.push_back(10);
		std_a.push_back(20);
		std_a.push_back(30);
		std::list<int> std_b;
		std_b.push_back(10);
		std_b.push_back(20);
		std_b.push_back(30);
		std_b.push_back(30);
		std::list<int> std_c;

		testBool((std_a != std_b), __LINE__);
		testBool(std_b != std_c, __LINE__);
		testBool(!(std_b < std_c), __LINE__);
		testBool(!(std_c > std_b), __LINE__);
		testBool((std_a <= std_b), __LINE__);
		testBool(std_a < std_b, __LINE__);

		std::cout << SUBTITLE << "[ Same values, same calls for ft ]" << RESET_COLOR << std::endl;

		ft::list<int> ft_a;
		ft_a.push_back(10);
		ft_a.push_back(20);
		ft_a.push_back(30);
		ft::list<int> ft_b;
		ft_b.push_back(10);
		ft_b.push_back(20);
		ft_b.push_back(30);
		ft_b.push_back(30);
		ft::list<int> ft_c;

		testBool((ft_a != ft_b), __LINE__);
		testBool(ft_b != ft_c, __LINE__);
		testBool(!(ft_b < ft_c), __LINE__);
		testBool(!(ft_c > ft_b), __LINE__);
		testBool((ft_a <= ft_b), __LINE__);
		testBool(ft_a < ft_b, __LINE__);
	}
	return(0);
}

int
test_splice( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with int ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ftl0(8, 0);
		ft::list<int>	ftl1(8, 1);
		std::list<int>	stdl0(8, 0);
		std::list<int>	stdl1(8, 1);

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);

		std::cout << SUBTITLE << "[ splice (entire list (1)) entire list 0 to begining of list 1 ]" << RESET_COLOR << std::endl;
		ftl1.splice(ftl1.begin(), ftl0);
		stdl1.splice(stdl1.begin(), stdl0);
		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (entire list (1)) entire list 1 to end of list 0 ]" << RESET_COLOR << std::endl;
		ftl0.splice(ftl0.end(), ftl1);
		stdl0.splice(stdl0.end(), stdl1);
		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);

		std::cout << SUBTITLE << "[ instanciate new empty list 3 and splice (entire list (1)) entire list 0 to end of list 3 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl3;
		std::list<int>	stdl3;
		ftl3.splice(ftl3.end(), ftl0);
		stdl3.splice(stdl3.end(), stdl0);
		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		testList(ftl3, stdl3,  NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ftl0(5, "HelloWorld!");
		ft::list<std::string>	ftl1(5, "bye!");
		std::list<std::string>	stdl0(5, "HelloWorld!");
		std::list<std::string>	stdl1(5, "bye!");

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer second element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = ++ftl0.begin();
		std::list<std::string>::iterator	std_itl0 = ++stdl0.begin();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
		stdl1.splice(stdl1.begin(), stdl0, std_itl0);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);
		std::cout << SUBTITLE << "[ check if previously list 0 iterator does iterate on list 1 now ]" << RESET_COLOR << std::endl;
		testBool( *(++ft_itl0) == "bye!" , __LINE__);
		testBool( *(++std_itl0) == "bye!" , __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ftl0(5, "HelloWorld!");
		ft::list<std::string>	ftl1(5, "bye!");
		std::list<std::string>	stdl0(5, "HelloWorld!");
		std::list<std::string>	stdl1(5, "bye!");

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the LAST element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = --ftl0.end();
		std::list<std::string>::iterator	std_itl0 = --stdl0.end();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
		stdl1.splice(stdl1.begin(), stdl0, std_itl0);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);

	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 1 HelloWorld, list 1 with 1 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ftl0(1, "HelloWorld!");
		ft::list<std::string>	ftl1(1, "bye!");
		std::list<std::string>	stdl0(1, "HelloWorld!");
		std::list<std::string>	stdl1(1, "bye!");

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the first (and only) element from list 0 to list 1 begin ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = ftl0.begin();
		std::list<std::string>::iterator	std_itl0 = stdl0.begin();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
		stdl1.splice(stdl1.begin(), stdl0, std_itl0);

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ftl0(8, 0);
		ft::list<int>	ftl1(8, 1);
		std::list<int>	stdl0(8, 0);
		std::list<int>	stdl1(8, 1);

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version):transfer list 0 elements from begin to begin + 4 to list 1 ]" << RESET_COLOR << std::endl;
		ft::list<int>::iterator		ft_itl0 = ftl0.begin();
		std::list<int>::iterator	std_itl0 = stdl0.begin();
		ft::list<int>::iterator		ft_it_4_l0 = ftl0.begin();
		std::list<int>::iterator	std_it_4_l0 = stdl0.begin();
		for (int i = 0; i < 4; ++i)	{
			ft_it_4_l0++;
			std_it_4_l0++;
		}

		testList(ftl0, stdl0,  NOPRINT, "before test on list 0");
		testList(ftl1, stdl1,  NOPRINT, "before test on list 1");
		std::cout << SUBTITLE << "[ splice here ]" << RESET_COLOR << std::endl;
		ftl1.splice(ftl1.begin(), ftl0, ft_itl0, ft_it_4_l0);
		stdl1.splice(stdl1.begin(), stdl0, std_itl0, std_it_4_l0);
		testList(ftl0, stdl0,  NOPRINT, "test on list 0");
		testList(ftl1, stdl1,  NOPRINT, "test on list 1");
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ftl0(8, 0);
		ft::list<int>	ftl1(8, 1);
		std::list<int>	stdl0(8, 0);
		std::list<int>	stdl1(8, 1);

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version): iterator begin of list 0 into list 1 until list 0 is empty ]" << RESET_COLOR << std::endl;

		while(ftl0.empty() == false && stdl0.empty() == false)	{
			ftl1.splice(ftl1.begin(), ftl0, ftl0.begin());
			stdl1.splice(stdl1.begin(), stdl0, stdl0.begin());
			testList(ftl0, stdl0,  NOPRINT);
			testList(ftl1, stdl1,  NOPRINT);
		}
		std::cout << SUBTITLE << "[ check if ft list 0 AND std list 0 are both empty ]" << RESET_COLOR << std::endl;
		testBool( ftl0.empty() == stdl0.empty());
		std::cout << SUBTITLE << "[ same opposite direction ( list 1 to list 0) ]" << RESET_COLOR << std::endl;

		while(ftl1.empty() == false && stdl1.empty() == false)	{
			ftl0.splice(ftl0.begin(), ftl1, ftl1.begin());
			stdl0.splice(stdl0.begin(), stdl1, stdl1.begin());
			testList(ftl0, stdl0,  NOPRINT);
			testList(ftl1, stdl1,  NOPRINT);
		}
		std::cout << SUBTITLE << "[ check if ft list 1 AND std list 1 are both empty ]" << RESET_COLOR << std::endl;
		testBool( ftl1.empty() == stdl1.empty());
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ftl0(8, 0);
		ft::list<int>	ftl1(8, 1);
		std::list<int>	stdl0(8, 0);
		std::list<int>	stdl1(8, 1);

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version): last element from list 0 to begining of list 1, back and forth 100 times]" << RESET_COLOR << std::endl;

		for (int i = 0; i < 100; i++)	{
			ftl1.splice(ftl1.begin(), ftl0, --ftl0.end());
			stdl1.splice(stdl1.begin(), stdl0, --stdl0.end());
			ftl0.splice(ftl0.begin(), ftl1, ftl1.begin());
			stdl0.splice(stdl0.begin(), stdl1, stdl1.begin());
		}
		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
	}
	return (0);
}


bool more_than_100 (const int& value) { return (value>100); }
bool more_than_10 (const int& value) { return (value>10); }
bool less_or_eq_10 (const int& value) { return (value<=10); }

int
test_remove_if( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate empty list ]" << RESET_COLOR << std::endl;
		ft::list<int>	ftl0;
		std::list<int>	stdl0;
		size_t			testSize = 3000000;
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>10 ]" << RESET_COLOR << std::endl;
		ftl0.remove_if(more_than_10);
		stdl0.remove_if(more_than_10);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ pushback " << testSize << " random values in list (same value for ft and std list, 0 <= val < 20) ]" << RESET_COLOR << std::endl;


		srand(reinterpret_cast<long unsigned int>(&stdl0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ftl0.push_back(val);
			stdl0.push_back(val);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>100 (no element will be removed) ]" << RESET_COLOR << std::endl;
		ftl0.remove_if(more_than_100);
		stdl0.remove_if(more_than_100);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value>10 ]" << RESET_COLOR << std::endl;
		ftl0.remove_if(more_than_10);
		stdl0.remove_if(more_than_10);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ remove_if with predicate: bool function returning true for value<=10 ]" << RESET_COLOR << std::endl;
		ftl0.remove_if(less_or_eq_10);
		stdl0.remove_if(less_or_eq_10);
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ same as before but list 0 is now empty ]" << RESET_COLOR << std::endl;
		ftl0.remove_if(less_or_eq_10);
		stdl0.remove_if(less_or_eq_10);
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
};

int
test_remove( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with doubles ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<double>	ftl0;
		std::list<double>	stdl0;
		size_t				testSize = 500000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random float values in list (same value for ft and std list, 0 <= val < 5) ]" << RESET_COLOR << std::endl;
		srand(reinterpret_cast<long unsigned int>(&stdl0));

		int		divider;
		float	val;
		for (size_t i = 0; i < testSize; i++)	{
			if (i < (testSize / 3) || i > (testSize / 2))	{
				divider = rand() % 5;
				val = static_cast<float>(rand() % 15) / ( (divider == 0) ? i + 1 : divider );
			}
			ftl0.push_back(val);
			stdl0.push_back(val);
		}
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (1) no arg ]" << RESET_COLOR << std::endl;
		testList(ftl0, stdl0, NOPRINT);
		stdl0.unique();
		ftl0.unique();
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as boolean function (same_integral_part) ]" << RESET_COLOR << std::endl;
		stdl0.unique(same_integral_part);
		ftl0.unique(same_integral_part);
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ unique (2) with binary predicate as a structure (is_near()) ]" << RESET_COLOR << std::endl;
		stdl0.unique(is_near());
		ftl0.unique(is_near());
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}


bool smaller_than ( int first, int second)	{ return ( first<second ); }
bool greater_than ( int first, int second)	{ return ( first>second ); }

int
test_merge( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 and odd values in list 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize * 2; i++)	{
			if (i % 2 == 0)	{
				ftl0.push_back(i);
				stdl0.push_back(i);
			}
			else	{
				ftl1.push_back(i);
				stdl1.push_back(i);
			}
		}
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list into itself ]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl0, greater_than);
		stdl0.merge(stdl0, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, greater_than);
		stdl0.merge(stdl1, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "DESCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " DESCENDING even values in list 0 and odd values in list 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = testSize * 2; i > 0 ; i--)	{
			if (i % 2 == 0)	{
				ftl0.push_back(i);
				stdl0.push_back(i);
			}
			else	{
				ftl1.push_back(i);
				stdl1.push_back(i);
			}
		}

		ftl1.push_back(1000);
		stdl1.push_back(1000);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with smaller_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, smaller_than);
		stdl0.merge(stdl1, smaller_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 1000000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0 and list 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&stdl0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ftl0.push_back(val);
			stdl0.push_back(val);
			val = rand() % 40;
			ftl1.push_back(val);
			stdl1.push_back(val);
		}
		ftl0.push_back(42);
		stdl0.push_back(42);
		ftl0.push_back(42);
		stdl0.push_back(42);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1, greater_than);
		stdl0.merge(stdl1, greater_than);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER - with merge(1)" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		ft::list<int>		ftl1;
		std::list<int>		stdl1;
		size_t				testSize = 1000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0 and list 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&stdl0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ftl0.push_back(val);
			stdl0.push_back(val);
			val = rand() % 40;
			ftl1.push_back(val);
			stdl1.push_back(val);
		}
		ftl0.push_back(42);
		stdl0.push_back(42);
		ftl0.push_back(42);
		stdl0.push_back(42);

		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the list 1 into list 0 with no compare argument (merge(1)) ]" << RESET_COLOR << std::endl;
		ftl0.merge(ftl1);
		stdl0.merge(stdl1);
		testList(ftl0, stdl0, NOPRINT);
		testList(ftl1, stdl1, NOPRINT);
	}
	return (0);
}


int
test_iterator( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER VALUES" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in list 0 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			ftl0.push_back(i);
		}
		ft::list<int>::iterator		ft_it = ftl0.begin();
		ft::list<int>::iterator		ft_it2 = ftl0.begin();
		ft::list<int>::iterator		ft_itend = ftl0.end();

		std::cout << SUBTITLE << "[ test operator< with iterator to begin < end ]" << RESET_COLOR << std::endl;
		testBool(ft_it < ft_itend, __LINE__);
		std::cout << SUBTITLE << "[ loop test iterator increment vs. iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < ftl0.size(); i++)
		{
			testBool((*ft_it == *(ft_it2 + i)), __LINE__);
			ft_it++;
		}
		std::cout << SUBTITLE << "[ test operator= ]" << RESET_COLOR << std::endl;
		ft_it2 = ft_it;
		testBool(ft_it == ft_it2, __LINE__);
		std::cout << SUBTITLE << "[ loop test iterator increment vs. iterator + i ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < ftl0.size(); i++)
		{
			testBool((*ft_it == *(ft_it2 - i)), __LINE__);
			ft_it--;
		}
		testBool(static_cast<size_t>(ft_itend - ft_it) == ftl0.size(), __LINE__);
	}
	std::cout << HEADER_TITLE << "TEST ITERATOR ARITHMETIC" << RESET_COLOR << std::endl;
	{
		ft::list<int>			l;
		l.push_back(0);
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		ft::list<int>::iterator it1 = ++l.begin();
		ft::list<int>::iterator it2 = l.begin() + 2;
		it1++;
		ft::list<int>::iterator ite1 = --l.end();
		ite1--;
		ft::list<int>::iterator ite2 = l.end() - 2;

		testBool(*it1 == 2, __LINE__);
		testBool(*ite1 == 4, __LINE__);
		testBool(*it1 == *it2, __LINE__);
		testBool(*ite1 == *ite2, __LINE__);
	}

	return (0);
}



int
test_sort( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "LIST FILLED WITH A RANDOM NUMBER OF RANDOM VALUES" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		srand(reinterpret_cast<long unsigned int>(&stdl0));
		size_t				testSize = rand() % 15000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into list 0]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 10000;
			ftl0.push_back(val);
			stdl0.push_back(val);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ sort list 0 with greater_than Compare ]" << RESET_COLOR << std::endl;
		ftl0.sort(greater_than);
		stdl0.sort(greater_than);
		testList(ftl0, stdl0, NOPRINT);

		std::cout << SUBTITLE << "[ sort list 0 with not argument ]" << RESET_COLOR << std::endl;
		ftl0.sort();
		stdl0.sort();
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}


int
test_reverse( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		size_t				testSize = 6;


		for (size_t i = 1; i < testSize; i++)	{
			ftl0.push_back(i);
			stdl0.push_back(i);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << HEADER_TITLE << "LIST FILLED WITH "<< testSize << " DESCENDING VALUES " << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ftl0.reverse();
		stdl0.reverse();
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 1 value in list, increasing size by 1, chaging oddness ]" << RESET_COLOR << std::endl;
		ftl0.push_back(42);
		stdl0.push_back(42);
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ftl0.reverse();
		stdl0.reverse();
		testList(ftl0, stdl0, NOPRINT);
	}
	{
		ft::list<int>		ftl0;
		std::list<int>		stdl0;
		srand(reinterpret_cast<long unsigned int>(&stdl0));
		size_t				testSize = rand() % 5000000;


		for (size_t i = 1; i < testSize; i++)	{
			int val = rand() % 100;
			ftl0.push_back(val);
			stdl0.push_back(val);
		}
		testList(ftl0, stdl0, NOPRINT);
		std::cout << HEADER_TITLE << "LIST FILLED WITH "<< testSize << " VALUES, A RANDOM NUMBER OF RANDOM VALUES " << RESET_COLOR << std::endl;
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ftl0.reverse();
		stdl0.reverse();
		testList(ftl0, stdl0, NOPRINT);
		std::cout << SUBTITLE << "[ push back 1 value in list, increasing size by 1, chaging oddness ]" << RESET_COLOR << std::endl;
		ftl0.push_back(42);
		stdl0.push_back(42);
		std::cout << SUBTITLE << "[ reverse with no arguments ]" << RESET_COLOR << std::endl;
		ftl0.reverse();
		stdl0.reverse();
		testList(ftl0, stdl0, NOPRINT);
	}
	return (0);
}



int
main( void )	{

	try {
		// test_instantiation();

		// test_push_back_push_front_pop_back_pop_front();
		// test_clear();
		// test_Capacities();
		// test_insert_erase();

		// test_operatorEqual();
		// test_resize();
		// test_assign();
		// test_member_swap();
		// test_nonmember_swap();
		// test_relational_operators();
		// test_splice();
		// test_remove_if();
		// test_remove();
		// test_merge();
		// test_sort();
		// test_iterator();
		test_reverseIterator();
		// test_reverse();

		if (DEBUG_MODE == 0)
		{
			std::cout << SUBTITLE << "ALL TESTS PASSED ~~~~~~>  " << RESET_COLOR;
			testBool(1 == 1);
		}
	}
	catch ( failedTest & )	{
		std::cout << SUBTITLE << "SOME TEST FAILED !! \t \xE2\x9D\x8C" << RESET_COLOR << std::endl;
		return (1);
	}
	return (0);
}
