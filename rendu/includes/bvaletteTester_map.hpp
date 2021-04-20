#ifndef BVALETTETESTER_MAP_HPP
# define BVALETTETESTER_MAP_HPP

#include "map.hpp"
#include "bvaletteTester.hpp"

/**	===========================================================================+
 *  ----------- TESTER FOR MAP ------------------------------------------------|
 **	===========================================================================+
*/

template< typename K, typename T>
void
putMap( ft::map<K, T> const & container, int errorPos = -1 )	{

	std::cout << PRINT_TITLE << "[ FT::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	std::cout << PRINT_TITLE << "[ size capacity map ]" << RESET_COLOR << " -> ";
	std::cout << container.capacity() << std::endl;
	typename ft::map<K, T>::iterator it = container.begin();
	typename ft::map<K, T>::iterator ite = container.end();

	int	printMax;

	if (container.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(container.size());
	for (int i = 0; container.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(container.size()))
			std::cout << ERROR_SOURCE << "ft: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "ft: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(container.size()))
		std::cout << " !!\t map size is too large to print... stoping here." << std::endl;
}

template< typename K, typename T>
void
putMap( std::map<K, T> const & container, int errorPos = -1 )	{

	std::cout << PRINT_STD_TITLE << "[ STD::map ]" << RESET_COLOR << std::endl;
	std::cout << PRINT_STD_TITLE << "[ size of map ]" << RESET_COLOR << " -> ";
	std::cout << container.size() << std::endl;
	std::cout << PRINT_STD_TITLE << "[ capacity of map ]" << RESET_COLOR << " -> ";
	std::cout << container.capacity() << std::endl;
	typename std::map<K, T>::const_iterator it = container.begin();
	typename std::map<K, T>::const_iterator ite = container.end();

	int	printMax;

	if (container.size() > 100)
		printMax = 10;
	else
		printMax = static_cast<int>(container.size());
	for (int i = 0; container.size() > 0 && i <= printMax && it != ite; it++, i++)
	{
		if (i == errorPos || i > static_cast<int>(container.size()))
			std::cout << ERROR_SOURCE << "std: [" << i << "] " << RESET_COLOR << *it << " -> " << &(*it) << std::endl;
		else
			std::cout << "std: [" << i << "] " <<*it << " -> " << &(*it) << std::endl;
	}
	if (printMax != static_cast<int>(container.size()))
		std::cout << " !!\t map size is too large to print... stoping here." << std::endl;
}


template< typename K, typename T>
void
testMap( ft::map<K, T> const & ft_vct, std::map<K, T> const &std_vct,
bool print, std::string message = "" )	{

	bool	success = true;

	if (message.empty() == false)
		std::cout << SUBTITLE << message << RESET_COLOR << std::endl;

	if (print == true)
	{
		putMap<T>(ft_vct);
		putMap<T>(std_vct);
	}

	if(ft_vct.size() != std_vct.size())	{
		if (print == false && success == true)
		{
			putMap<T>(ft_vct);
			putMap<T>(std_vct);
		}
		std::cout << TITLE <<"size: ft (" << ft_vct.size() << ") std (" << std_vct.size() << ") Diff ! " << RESET_COLOR << std::endl;
		std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
		if (DEBUG_MODE < 1)
			throw failedTest();
		else
			success = false;
	}

	if (ft_vct.size() > 0)
	{
		int i = 0;
		typename ft::map<K, T>::iterator	ft_it = ft_vct.begin();
		typename ft::map<K, T>::iterator	ft_ite = ft_vct.end();

		typename std::map<K, T>::const_iterator	std_it = std_vct.begin();
		typename std::map<K, T>::const_iterator	std_ite = std_vct.end();
		while (ft_it != ft_ite && std_it != std_ite)	{

			if(*ft_it != *std_it)	{
				if (print == false && success == true)
				{
					putMap<T>(ft_vct, i);
					putMap<T>(std_vct, i);
				}
				std::cout << TITLE <<"iterator at pos " << i << ": ft (" << *ft_it << ") " << RESET_COLOR;
				std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
				std::cout << "std (" << *std_it << ") Diff ! " << RESET_COLOR << std::endl;
				if (DEBUG_MODE < 1)
					throw failedTest();
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
				putMap<T>(ft_vct);
				putMap<T>(std_vct);
			}
			std::cout << TITLE <<"Diff in map after iterating thought it." << RESET_COLOR << std::endl;
			std::cout << ERROR_TITLE << "ERROR !" << RESET_COLOR << std::endl;
			if (DEBUG_MODE < 1)
				throw failedTest();
			else
				success = false;
		}
	}

	if (print == true && success == true)
		std::cout << TESTOK_TITLE << "[ TEST PASSED: no diff ] map size: ft(" << ft_vct.size() << ") std(" << std_vct.size() << ") / capacity: ft(" << ft_vct.capacity() << ") std(" << std_vct.capacity() << ")" << RESET_COLOR << "\t  \342\234\205" << std::endl;
	else if (success == true)
		std::cout << "[ TEST PASSED: no diff ] map size: ft(" << ft_vct.size() << ") std(" << std_vct.size() << ") / capacity: ft(" << ft_vct.capacity() << ") std(" << std_vct.capacity() << ") \t \342\234\205" << std::endl;
	else
		std::cout << ERROR_TITLE << "TEST FAILED !" << RESET_COLOR << std::endl;
}

/**	===========================================================================+
 *  ----------- TESTER FUNCTIONS ----------------------------------------------|
 **	===========================================================================+
*/

int	main_tester_map( void );

int	test_map_instantiation( void );
int	test_map_push_back_pop_back( void );
int	test_map_clear( void );
int	test_map_capacities( void );
int	test_map_insert_erase( void );
int	test_map_operatorEqual( void );
int	test_map_resize( void );
int	test_map_assign( void );
int	test_map_at_operatorBrackets( void );
int	test_map_member_swap( void );
int	test_map_nonmember_swap( void );
int	test_map_relational_operators( void );
int	test_map_splice( void );
int	test_map_remove_if( void );
int	test_map_remove( void );
int	test_map_unique( void );
int	test_map_merge( void );
int	test_map_sort( void );
int	test_map_iterator( void );
int	test_map_reverseIterator( void );
int	test_map_reverse( void );
int	test_map_element_access( void );

#endif