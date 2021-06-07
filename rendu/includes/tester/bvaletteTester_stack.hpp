#ifndef BVALETTETESTER_STACK_HPP
# define BVALETTETESTER_STACK_HPP

# include "../stack/stack.hpp"
# include "./tester/bvaletteTester.hpp"

/**	===========================================================================+
 *  ----------- TESTER FOR DEQUE  ---------------------------------------------|
 **	===========================================================================+
*/

// template< typename T>
// void
// putStack( ft::stack<T> const & vct, int errorPos = -1 )	{

// 	std::cout << PRINT_TITLE << "[ FT::stack ]" << RESET_COLOR << std::endl;
// 	std::cout << PRINT_TITLE << "[ size of stack ]" << RESET_COLOR << " -> ";
// 	std::cout << vct.size() << std::endl;
// 	typename ft::stack<T>::const_iterator it = vct.begin();
// 	typename ft::stack<T>::const_iterator ite = vct.end();

// 	int	printMax;

// 	if (vct.size() > 100)
// 		printMax = 10;
// 	else
// 		printMax = static_cast<int>(vct.size());
// 	for (int i = 0; vct.size() > 0 && i <= printMax && it != ite; it++, i++)
// 	{
// 		if (i == errorPos || i > static_cast<int>(vct.size()))
// 			std::cout << ERROR_SOURCE << "ft: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
// 		else
// 			std::cout << "ft: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
// 	}
// 	if (printMax != static_cast<int>(vct.size()))
// 		std::cout << " !!\t stack size is too large to print... stoping here." << std::endl;
// }

// template< typename T>
// void
// putStack( std::stack<T> const & vct, int errorPos = -1 )	{

// 	std::cout << PRINT_STD_TITLE << "[ STD::stack ]" << RESET_COLOR << std::endl;
// 	std::cout << PRINT_STD_TITLE << "[ size of stack ]" << RESET_COLOR << " -> ";
// 	std::cout << vct.size() << std::endl;
// 	typename std::stack<T>::const_iterator it = vct.begin();
// 	typename std::stack<T>::const_iterator ite = vct.end();

// 	int	printMax;

// 	if (vct.size() > 100)
// 		printMax = 10;
// 	else
// 		printMax = static_cast<int>(vct.size());
// 	for (int i = 0; vct.size() > 0 && i <= printMax && it != ite; it++, i++)
// 	{
// 		if (i == errorPos || i > static_cast<int>(vct.size()))
// 			std::cout << ERROR_SOURCE << "std: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
// 		else
// 			std::cout << "std: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
// 	}
// 	if (printMax != static_cast<int>(vct.size()))
// 		std::cout << " !!\t stack size is too large to print... stoping here." << std::endl;
// }


template< typename T>
void
testStack( ft::stack<T> const & ft_vct, std::stack<T> const &std_vct,
bool print, std::string message = "" )	{

	(void)ft_vct;
	(void)std_vct;
	(void)print;
	(void)message;

	// bool	success = true;

	// if (message.empty() == false)
	// 	std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	// if (print == true)
	// {
	// 	putStack<T>(ft_vct);
	// 	putStack<T>(std_vct);
	// }

	// if(ft_vct.size() != std_vct.size())	{
	// 	if (print == false && success == true)
	// 	{
	// 		putStack<T>(ft_vct);
	// 		putStack<T>(std_vct);
	// 	}
	// 	std::cout << TITLE <<"size: ft (" << ft_vct.size() << ") std (" << std_vct.size() << ") Diff ! " << RESET_COLOR << std::endl;
	// 	std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
	// 	if (DEBUG_MODE < 1)
	// 		throw failedTest();
	// 	else
	// 		success = false;
	// }

	// if (ft_vct.size() > 0)
	// {
	// 	int i = 0;
	// 	typename ft::stack<T>::const_iterator	ft_it = ft_vct.begin();
	// 	typename ft::stack<T>::const_iterator	ft_ite = ft_vct.end();

	// 	typename std::stack<T>::const_iterator	std_it = std_vct.begin();
	// 	typename std::stack<T>::const_iterator	std_ite = std_vct.end();
	// 	while (ft_it != ft_ite && std_it != std_ite)	{

	// 		if(*ft_it != *std_it)	{
	// 			if (print == false && success == true)
	// 			{
	// 				putStack<T>(ft_vct, i);
	// 				putStack<T>(std_vct, i);
	// 			}
	// 			std::cout << TITLE <<"iterator at pos " << i << ": ft (" << *ft_it << ") " << RESET_COLOR;
	// 			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
	// 			std::cout << "std (" << *std_it << ") Diff ! " << RESET_COLOR << std::endl;
	// 			if (DEBUG_MODE < 1)
	// 				throw failedTest();
	// 			else
	// 				success = false;
	// 		}
	// 		i++;
	// 		ft_it++;
	// 		std_it++;
	// 	}
	// 	if (ft_it != ft_ite || std_it != std_ite)	{
	// 		if (print == false && success == true)
	// 		{
	// 			putStack<T>(ft_vct);
	// 			putStack<T>(std_vct);
	// 		}
	// 		std::cout << TITLE <<"Diff in stack after iterating thought it." << RESET_COLOR << std::endl;
	// 		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
	// 		if (DEBUG_MODE < 1)
	// 			throw failedTest();
	// 		else
	// 			success = false;
	// 	}
	// }

	// if (print == true && success == true)
	// 	std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ] stack size: ft(" << ft_vct.size() << ") std( " << std_vct.size() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	// else if (success == true)
	// 	std::cout << "[ TEST PASSED: no diff ] stack size: ft(" << ft_vct.size() << ") std( " << std_vct.size() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	// else
	// 	std::cout << ERROR_TITLE << "TEST FAILED !" << RESET_COLOR << std::endl;
}

/**	===========================================================================+
 *  ----------- TESTER FUNCTIONS ----------------------------------------------|
 **	===========================================================================+
*/

int	main_tester_stack( void );

int	test_stack_general( void );

#endif
