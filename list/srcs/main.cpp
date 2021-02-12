/**
 * Compilation may change DEBUG_MODE setting to
 *
 * 	DEBUG_MODE=0 -> no special output
 * 	DEBUG_MODE=1 -> continue after test a failed (abort otherwise)
 * 				 	+ minimal informations (mainly constructor/destructor calls)
 * 	DEBUG_MODE=2 -> more indepth infos
*/


#include "list.hpp"

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

#ifndef PRINT_TITLE
# define PRINT_TITLE    "\n\033[44m\t"
#endif

#ifndef TESTOK_TITLE
# define TESTOK_TITLE    "\n\033[102m\t"
#endif

#ifndef PRINT
# define PRINT		true
#endif

# define NOPRINT	false


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
putList( ft::list<T> const & lst, size_t errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ FT::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of list ]" << RESET_COLOR << " -> ";
	std::cout << lst.size() << std::endl;
	typename ft::list<T>::iterator it = lst.begin();
	typename ft::list<T>::iterator ite = lst.end();

	for (size_t i = 0; lst.size() > 0 && i <= lst.size() && it != ite; it++, i++)
	{
		if (i == errorPos || i == lst.size())
			std::cout << ERROR_SOURCE << "ft: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "ft: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
}

template< typename T>
void
putList( std::list<T> const & lst, size_t errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ STD::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of list ]" << RESET_COLOR << " -> ";
	std::cout << lst.size() << std::endl;
	typename std::list<T>::const_iterator it = lst.begin();
	typename std::list<T>::const_iterator ite = lst.end();

	for (size_t i = 0; lst.size() > 0 && i <= lst.size() && it != ite; it++, i++)
	{
		if (i == errorPos || i == lst.size())
			std::cout << ERROR_SOURCE << "std: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "std: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
}

bool	testBool(bool b, int const lineNo = -1 )	{
	if (b == true)
		std::cout << "[ TEST PASSED: no diff ] \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "[ FAILURE at line..." << lineNo << "]" << RESET_COLOR << " \342\235\214" << std::endl;
	return (b);
}

template< typename T>
void
testList( ft::list<T> const & ft_lst, std::list<T> const &std_lst, bool print, std::string message = "" )	{


	if (message.empty() == false)
		std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	if (print == true)
	{
		putList<T>(std_lst);
		putList<T>(ft_lst);
	}

	if(ft_lst.size() != std_lst.size())	{
		if (print == false)
		{
			putList<T>(std_lst);
			putList<T>(ft_lst);
		}
		std::cout << TITLE <<"size: ft (" << ft_lst.size() << ") std (" << std_lst.size() << ") Diff ! " << RESET_COLOR << std::endl;
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
			abort();
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
				if (print == false)
				{
					putList<T>(ft_lst, i);
					putList<T>(std_lst, i);
				}
				std::cout << TITLE <<"iterator at pos " << i << ": ft (" << *ft_it << ") " << RESET_COLOR;
				std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
				std::cout << "std (" << *std_it << ") Diff ! " << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
					abort();
			}
			i++;
			ft_it++;
			std_it++;
		}
		if (ft_it != ft_ite || std_it != std_ite)	{
			if (print == false)
			{
				putList<T>(ft_lst);
				putList<T>(std_lst);
			}
			std::cout << TITLE <<"Diff in list after iterating thought it." << RESET_COLOR << std::endl;
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
				abort();
		}
	}
	if (print == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ]" << RESET_COLOR << " \342\234\205" << std::endl;
	else
		std::cout << "[ TEST PASSED: no diff ]" << " \342\234\205" << std::endl;
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

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		ft::list<int>				lst;

		lst.push_front(43);
		lst.push_front(42);
		lst.push_front(41);

		putList<int>(lst);


		std::cout << SUBTITLE << "[ begin and rbegin ]" << RESET_COLOR << std::endl;
		ft::list<int>::iterator		it = lst.begin();
		ft::list<int>::reverse_iterator		rit = lst.rbegin();
		std::cout << "begin --> " << *it << " - " << &(*it) << std::endl;
		std::cout << "rbegin -> " << *rit << " - " << &(*rit) << std::endl;

		std::cout << SUBTITLE << "[ end and rend ]" << RESET_COLOR << std::endl;
		it = lst.end();
		rit = lst.rend();
		it--;
		rit--;
		std::cout << "end - 1 --> " << *it << " - " << &(*it) << std::endl;
		std::cout << "rend - 1 -> " << *rit << " - " << &(*rit) << std::endl;

	}
	{
		std::list<int>				lst;

		lst.push_front(43);
		lst.push_front(42);
		lst.push_front(41);


		std::cout << SUBTITLE << "[ with STD::LIST begin and rbegin ]" << RESET_COLOR << std::endl;
		std::list<int>::iterator				it = lst.begin();
		std::list<int>::reverse_iterator		rit = lst.rbegin();
		std::cout << "begin --> " << *it << " - " << &(*it) << std::endl;
		std::cout << "rbegin -> " << *rit << " - " << &(*rit) << std::endl;

		std::cout << SUBTITLE << "[ with STD::LIST end and rend ]" << RESET_COLOR << std::endl;
		it = lst.end();
		rit = lst.rend();
		it--;
		rit--;
		std::cout << "end - 1 --> " << *it << " - " << &(*it) << std::endl;
		std::cout << "rend - 1 -> " << *rit << " - " << &(*rit) << std::endl;
	}
	return(0);
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
	// {
	// 	std::cout << SUBTITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

	// 	ft::list<std::string>	ftl0(5, "HelloWorld!");
	// 	ft::list<std::string>	ftl1(5, "bye!");
	// 	std::list<std::string>	stdl0(5, "HelloWorld!");
	// 	std::list<std::string>	stdl1(5, "bye!");

	// 	testList(ftl0, stdl0, NOPRINT);
	// 	testList(ftl1, stdl1, NOPRINT);
	// 	std::cout << SUBTITLE << "[ splice (single element(2) version):transfer second element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
	// 	ft::list<std::string>::iterator		ft_itl0 = ++ftl0.begin();
	// 	std::list<std::string>::iterator	std_itl0 = ++stdl0.begin();

	// 	void * ft_ptr_splicedElem = &(*ft_itl0);
	// 	void * std_ptr_splicedElem = &(*std_itl0);

	// 	ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
	// 	stdl1.splice(stdl1.begin(), stdl0, std_itl0);

	// 	testList(ftl0, stdl0, NOPRINT);
	// 	testList(ftl1, stdl1, NOPRINT);

	// 	std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
	// 	testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
	// 	testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);
	// 	std::cout << SUBTITLE << "[ check if previously list 0 iterator does iterate on list 1 now ]" << RESET_COLOR << std::endl;
	// 	testBool( *(++ft_itl0) == "bye!" , __LINE__);
	// 	testBool( *(++std_itl0) == "bye!" , __LINE__);
	// }
	// {
	// 	std::cout << SUBTITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

	// 	ft::list<std::string>	ftl0(5, "HelloWorld!");
	// 	ft::list<std::string>	ftl1(5, "bye!");
	// 	std::list<std::string>	stdl0(5, "HelloWorld!");
	// 	std::list<std::string>	stdl1(5, "bye!");

	// 	testList(ftl0, stdl0, NOPRINT);
	// 	testList(ftl1, stdl1, NOPRINT);
	// 	std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the LAST element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
	// 	ft::list<std::string>::iterator		ft_itl0 = --ftl0.end();
	// 	std::list<std::string>::iterator	std_itl0 = --stdl0.end();

	// 	void * ft_ptr_splicedElem = &(*ft_itl0);
	// 	void * std_ptr_splicedElem = &(*std_itl0);

	// 	ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
	// 	stdl1.splice(stdl1.begin(), stdl0, std_itl0);

	// 	testList(ftl0, stdl0, NOPRINT);
	// 	testList(ftl1, stdl1, NOPRINT);

	// 	std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
	// 	testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
	// 	testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);

	// }
	// {
	// 	std::cout << SUBTITLE << "[ list 0 with 1 HelloWorld, list 1 with 1 Bye! ]" << RESET_COLOR << std::endl;

	// 	ft::list<std::string>	ftl0(1, "HelloWorld!");
	// 	ft::list<std::string>	ftl1(1, "bye!");
	// 	std::list<std::string>	stdl0(1, "HelloWorld!");
	// 	std::list<std::string>	stdl1(1, "bye!");

	// 	testList(ftl0, stdl0,  NOPRINT);
	// 	testList(ftl1, stdl1,  NOPRINT);
	// 	std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the first (and only) element from list 0 to list 1 begin ]" << RESET_COLOR << std::endl;
	// 	ft::list<std::string>::iterator		ft_itl0 = ftl0.begin();
	// 	std::list<std::string>::iterator	std_itl0 = stdl0.begin();

	// 	void * ft_ptr_splicedElem = &(*ft_itl0);
	// 	void * std_ptr_splicedElem = &(*std_itl0);

	// 	ftl1.splice(ftl1.begin(), ftl0, ft_itl0);
	// 	stdl1.splice(stdl1.begin(), stdl0, std_itl0);

	// 	testList(ftl0, stdl0,  NOPRINT);
	// 	testList(ftl1, stdl1,  NOPRINT);

	// 	std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
	// 	testBool( ft_ptr_splicedElem ==  &(*ftl1.begin()),__LINE__);
	// 	testBool( std_ptr_splicedElem ==  &(*stdl1.begin()),__LINE__);
	// }
	{
		std::cout << SUBTITLE << "[ list 0 with 1 HelloWorld, list 1 with 1 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ftl0(8, "HelloWorld!");
		ft::list<std::string>	ftl1(8, "bye!");
		std::list<std::string>	stdl0(8, "HelloWorld!");
		std::list<std::string>	stdl1(8, "bye!");

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version):transfer list 0 elements from begin to begin + 4 to list 1 ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = ftl0.begin();
		std::list<std::string>::iterator	std_itl0 = stdl0.begin();
		ft::list<std::string>::iterator		ft_it_end_l0 = ftl0.begin();
		std::list<std::string>::iterator	std_it_end_l0 = stdl0.begin();
		for (int i = 0; i < 4; ++i)	{
			ft_it_end_l0++;
			std_it_end_l0++;
		}

		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		ftl1.splice(ftl1.begin(), ftl0, ft_itl0, ft_it_end_l0);
		stdl1.splice(stdl1.begin(), stdl0, std_itl0, std_it_end_l0);
		testList(ftl0, stdl0,  NOPRINT);
		testList(ftl1, stdl1,  NOPRINT);
		// testList(ftl0, stdl0,  NOPRINT);
		// testList(ftl1, stdl1,  NOPRINT);
		// ftl1.splice(ftl1.end(), ftl0, ft_itl0, ft_it_end_l0);
		// stdl1.splice(stdl1.end(), stdl0, std_itl0, std_it_end_l0);
		// testList(ftl0, stdl0,  NOPRINT);
		// testList(ftl1, stdl1,  NOPRINT);

	}
	return (0);
}

int
main( void )	{

	// test_instantiation();

	// test_push_back_push_front_pop_back_pop_front();
	// test_clear();
	// test_Capacities();
	// test_insert_erase();
	// test_reverseIterator();

	// test_operatorEqual();
	// test_resize();
	// test_assign();
	// test_member_swap();
	// test_nonmember_swap();
	// test_relational_operators();
	test_splice();

	if (DEBUG_MODE == 0)
	{
		std::cout << SUBTITLE << "ALL TESTS PASSED ~~~~~~>  " << RESET_COLOR;
		testBool(true);
	}
	return (0);
}
