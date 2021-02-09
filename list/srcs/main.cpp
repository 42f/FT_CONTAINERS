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

#ifndef SUBTITLE
# define SUBTITLE    "\n\033[7m"
#endif

#ifndef PRINT_TITLE
# define PRINT_TITLE    "\n\033[44m\t"
#endif

#ifndef TESTOK_TITLE
# define TESTOK_TITLE    "\n\033[102m\t"
#endif

# define PRINT		true
# define NOPRINT	false


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
void	putList( ft::list<T> const & lst, int errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ FT::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of list ]" << RESET_COLOR << std::endl;
	std::cout << lst.size();
	std::cout << PRINT_TITLE << "[ read iterator from begin to  begin to end + 2 ]" << RESET_COLOR << std::endl;
	typename ft::list<T>::iterator it = lst.begin();
	typename ft::list<T>::iterator ite = lst.end();

	for (int i = 0; it != ite; it++, i++)
	{
		if (i == errorPos)
			std::cout << ERROR_TITLE << "[" << i << "] " <<*it << " -> " << &(*it) << RESET_COLOR << std::endl;
		else
			std::cout << "[" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
}

template< typename T>
void	putList( std::list<T> const & lst, int errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ STD::LIST ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of list ]" << RESET_COLOR << std::endl;
	std::cout << lst.size();
	std::cout << PRINT_TITLE << "[ read iterator from begin to  begin to end + 2 ]" << RESET_COLOR << std::endl;
	typename std::list<T>::const_iterator it = lst.begin();
	typename std::list<T>::const_iterator ite = lst.end();

	for (int i = 0; it != ite; it++, i++)
	{
		if (i == errorPos)
			std::cout << ERROR_TITLE << "[" << i << "] " <<*it << " -> " << &(*it) << RESET_COLOR << std::endl;
		else
			std::cout << "[" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
}

template< typename T>
void	testList( ft::list<T> const & ft_lst, std::list<T> const &std_lst, bool print )	{

	typename ft::list<T>::iterator	ft_it = ft_lst.begin();
	typename ft::list<T>::iterator	ft_ite = ft_lst.end();

	typename std::list<T>::const_iterator	std_it = std_lst.begin();
	typename std::list<T>::const_iterator	std_ite = std_lst.end();

	if (print == true)
	{
		putList<T>(ft_lst);
		putList<T>(std_lst);
	}

	int i = 0;
	while (ft_it != ft_ite && std_it != std_ite)	{

		if(*ft_it != *std_it)	{
			if (print == false)
			{
				putList<T>(ft_lst, i);
				putList<T>(std_lst, i);
			}
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
			std::cout << TITLE <<"iterator at pos " << i << ": ft (" << *ft_it << ") ";
			std::cout << "std (" << *std_it << ") Diff ! " << RESET_COLOR << std::endl;
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
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		std::cout << TITLE <<"Diff in list after iterating thought it." << RESET_COLOR << std::endl;
		abort();
	}

	if(ft_lst.size() != std_lst.size())	{
		if (print == false)
		{
			putList<T>(ft_lst);
			putList<T>(std_lst);
		}
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		std::cout << TITLE <<"size: ft (" << ft_lst.size() << ") std (" << std_lst.size() << ") Diff ! " << RESET_COLOR << std::endl;
		abort();
	}
	if (print == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED ]" << RESET_COLOR << std::endl;
}

void 	handler(int sig) {
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

int		test_Capacities( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		assert(std.empty() == ft.empty());
	}
	{
		size_t		testSize = 5;
		std::cout << SUBTITLE << "[ Size on list with " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<int>	std(testSize);
		ft::list<int>	ft(testSize);

		std::cout << "Size of std : " << std.size() << std::endl;
		std::cout << "Size of ft  : " << ft.size() << std::endl;

		assert(std.size() == ft.size());

		std::cout << "empty for std : " << std::boolalpha << std.empty() << std::endl;
		std::cout << "empty for ft  : " << std::boolalpha << ft.empty() << std::endl;

		assert(std.empty() == ft.empty());

	}
	{
		size_t		testSize = 0;
		std::cout << SUBTITLE << "[ max_size for a list of " << testSize << " elements ]" << RESET_COLOR << std::endl;
		std::list<float>	std(testSize);
		ft::list<float>		ft(testSize);
		std::cout << "max_size for std : " << std.max_size() << std::endl;
		std::cout << "max_size for ft  : " << ft.max_size() << std::endl;
		assert(std.max_size() == ft.max_size());

	}
	return (0);
}

int		test_operatorEqual( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << __LINE__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

  std::list<int> first (3);      // list of 3 zero-initialized ints
  std::list<int> second (5);     // list of 5 zero-initialized ints

	first.push_front(42);
	second.push_front(99);

  std::cout << "first:   front " << first.front()  << " @ " <<  &(first.front()) << std::endl;
  std::cout << "second:  front " << second.front() << " @ " <<  &(second.front()) <<  std::endl;
  std::cout << "first:   back " << first.back()  << " @ " <<  &(first.back()) << " size lst = " << first.size() << std::endl;
  std::cout << "second:  back " << second.back() << " @ " <<  &(second.back()) << " size lst = " << second.size() << std::endl;


	std::cout << SUBTITLE << "[ list second = list first ]" << RESET_COLOR << std::endl;
  second = first;
//   first = std::list<int>();

  std::cout << "first:   front " << first.front()  << " @ " <<  &(first.front()) << std::endl;
  std::cout << "second:  front " << second.front() << " @ " <<  &(second.front()) <<  std::endl;
  std::cout << "first:   back " << first.back()  << " @ " <<  &(first.back()) << " size lst = " << first.size() << std::endl;
  std::cout << "second:  back " << second.back() << " @ " <<  &(second.back()) << " size lst = " << second.size() << std::endl;
	return (0);
}

int		test_push_back_push_front_pop_back_pop_front( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	ft::list<int> lst;

	std::cout << SUBTITLE << "[ push_back 10 times ]" << RESET_COLOR << std::endl;

	for (size_t i = 0; i < 10; i++)
		lst.push_back(i + 100);

	putList<int>(lst);

	std::cout << SUBTITLE << "[ pop_back 3 times ]" << RESET_COLOR << std::endl;
	lst.pop_back();
	lst.pop_back();
	lst.pop_back();

	putList<int>(lst);

	std::cout << SUBTITLE << "[ push_front values: 99, 999 and 9999 ]" << RESET_COLOR << std::endl;
	lst.push_front(99);
	lst.push_front(999);
	lst.push_front(9999);

	putList<int>(lst);

	{
		std::cout << SUBTITLE << "[ NEW EMPTY list: push_front 99, 999 and 9999 on empty list ]" << RESET_COLOR << std::endl;
		ft::list<int> lst;
		lst.push_front(99);
		lst.push_front(999);
		lst.push_front(9999);

		putList<int>(lst);

		std::cout << SUBTITLE << "[ pop_front() once ]" << RESET_COLOR << std::endl;
		lst.pop_front();
		putList<int>(lst);

		std::cout << SUBTITLE << "[ pop_front() 10 times ]" << RESET_COLOR << std::endl;
		for (int i = 0; i < 10; i++)
			lst.pop_front();
		putList<int>(lst);

		std::list<int> stdlst(1, 42);
		std::list<int>::iterator itstd = stdlst.begin();
		std::cout << &(*itstd) << std::endl;
		stdlst.pop_front();
		itstd = stdlst.begin();
		std::cout << &(*itstd) << std::endl;
		// stdlst.push_back(21);
		// std::cout << &(stdlst.front()) << std::endl;

	}
	return (0);
}
int		test_instantiation( void )	{

	{
	// 	ft::list<int>	lst(8, 42);
	// 	(void)lst;
	// 	std::cout << lst << std::endl;

	// 	std::cout << "size -> " << lst.size() << std::endl;
	// 	std::cout << "front-> " << lst.front() << std::endl;
	// 	std::cout << "back -> " << lst.back() << std::endl;

	// 	ft::list<int>::iterator	it = lst.begin();
	// 	ft::list<int>::iterator	ite = lst.end();

	// 	std::cout << "it => " << *it << std::endl;
	// 	std::cout << "ite=> " << *ite << std::endl;
	// std::cout << "++it and --ite" << std::endl;
	// ++it;
	// --ite;

	// 	std::cout << "it => " << *it << std::endl;
	// 	std::cout << "ite=> " << *ite << std::endl;

	// std::cout << "--it and ++ite" << std::endl;
	// --it;
	// ++ite;
	// 	std::cout << "it => " << *it << std::endl;
	// 	std::cout << "ite=> " << *ite << std::endl;

	// std::cout << "OUTSIDE : --it and ++ite" << std::endl;
	// --it;
	// ++ite;
	// 	std::cout << "it => " << (*it) << std::endl;
	// 	std::cout << "ite=> " << (*ite) << std::endl;
	}

	// std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;

	// std::cout << SUBTITLE << "[ lst0 default ]" << RESET_COLOR << std::endl;
	// ft::list<int>	lst0;
	// std::cout << SUBTITLE << "[ lst1 default with type custom class ]" << RESET_COLOR << std::endl;
	// ft::list<ex>	lst1;

	// std::cout << SUBTITLE << "[ lst2 with size and value ]" << RESET_COLOR << std::endl;
	// int value = 42;
	// ft::list<int>	lst2(10, value);
	// std::cout << "instance is @ " << &lst2 << std::endl;
	// std::cout << "value at front lst2: " << lst2.front() << std::endl;
	// assert(lst2.front() == value);
	return (0);
}

int		test_reverseIterator( void )	{

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

int		test_insert_erase( void )	{
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
			ftl1.erase(--ftl1.end());
			stdl1.erase(--stdl1.end());
		}
		ftl1.erase(ftl1.begin());
		stdl1.erase(stdl1.begin());

		testList(ftl1, stdl1, PRINT);
		std::cout << SUBTITLE << "[ Erase with erase(iterator, iterator) ]" << RESET_COLOR << std::endl;
		for (int i = 0; i < 3; i++)
		{
			ftl1.erase(--ftl1.end());
			stdl1.erase(--stdl1.end());
		}
		ftl1.erase(ftl1.begin(), ftl1.end());
		stdl1.erase(stdl1.begin(), stdl1.end());

		testList(ftl1, stdl1, PRINT);

	}
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with int ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<int>	ftl0;
		std::list<int>	stdl0;

		int	val = 42;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ftl0.insert(ftl0.end(), 5, val);
		ftl0.push_front(0);
		ftl0.push_back(99);

		stdl0.insert(stdl0.end(), 5, val);
		stdl0.push_front(0);
		stdl0.push_back(99);

		testList(ftl0, stdl0, NOPRINT);

		ft::list<int>	ftl1;
		std::list<int>	stdl1;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;
		ftl1.insert(ftl1.begin(), ftl0.begin(), ftl0.end());
		stdl1.insert(stdl1.begin(), stdl0.begin(), stdl0.end());

		testList(ftl1, stdl1, NOPRINT);
	}
	return (0);
}

int		main( void )	{

	// test_instantiation();
	// test_push_back_push_front_pop_back_pop_front();
	// test_Capacities();
	test_insert_erase();
	// test_reverseIterator();
	// test_operatorEqual();
	return (0);
}
