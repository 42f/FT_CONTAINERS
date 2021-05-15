/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_insert_erase.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:19 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/22 11:53:46 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exampleClass.hpp"
#include "bvaletteTester_map.hpp"

void
testBasicInsertMemberFunction ( void )	{
		std::cout << HEADER_TITLE << "[ Insert with two different Compare functions]" << RESET_COLOR << std::endl;
		{
			std::map<char, int, std::greater<char> >	std_first_greater;
			std_first_greater.insert(std::pair<char, int>('a',10));
			std_first_greater.insert(std::pair<char, int>('b',30));
			std_first_greater.insert(std::pair<char, int>('c',50));
			std_first_greater.insert(std::pair<char, int>('d',70));
			ft::map<char, int, std::greater<char> >	ft_first_greater;
			ft_first_greater.insert(ft::pair<char, int>('a',10));
			ft_first_greater.insert(ft::pair<char, int>('b',30));
			ft_first_greater.insert(ft::pair<char, int>('c',50));
			ft_first_greater.insert(ft::pair<char, int>('d',70));

			std::map<char, int, std::greater<char> >::iterator	std_it = std_first_greater.begin();
			std::map<char, int, std::greater<char> >::iterator	std_ite = std_first_greater.end();
			ft::map<char, int, std::greater<char> >::iterator	ft_it = ft_first_greater.begin();
			ft::map<char, int, std::greater<char> >::iterator	ft_ite = ft_first_greater.end();

			std::map<char, int>	std_c0;
			ft::map<char, int>	ft_c0;
			std_c0.insert(std_it, std_ite);
			ft_c0.insert(ft_it, ft_ite);

			testMap<char, int, std::greater<char> >(ft_first_greater, std_first_greater, NOPRINT);
			testMap<char, int>(ft_c0, std_c0, NOPRINT);
		}
}

void
testCppRefCode( void )	{
	std::cout << HEADER_TITLE << "[ Insert with code from Cpp reference]" << RESET_COLOR << std::endl;
	std::map<char,int> std_c0;
	ft::map<char,int> ft_c0;

	std::cout << HEADER_TITLE << "[ Insert Function ]" << RESET_COLOR << std::endl;
	// first insert function version (single parameter):
	std_c0.insert ( std::pair<char,int>('a',100) );
	std_c0.insert ( std::pair<char,int>('z',200) );
	ft_c0.insert ( ft::pair<char,int>('a',100) );
	ft_c0.insert ( ft::pair<char,int>('z',200) );

	testMap<char, int>(ft_c0, std_c0, NOPRINT);


	std::cout << HEADER_TITLE << "[ Test boolean returned in a pair in case of pre existing element ]" << RESET_COLOR << std::endl;
	std::pair<std::map<char,int>::iterator,bool> std_ret = std_c0.insert ( std::pair<char,int>('z',500) );
	ft::pair<ft::map<char,int>::iterator,bool> ft_ret = ft_c0.insert ( ft::pair<char,int>('z',500) );
	testBool((std_ret.second == ft_ret.second), __LINE__);
	testMap<char, int>(ft_c0, std_c0, NOPRINT);

	std::cout << HEADER_TITLE << "[ Insert with hint ]" << RESET_COLOR << std::endl;
	// second insert function version (with hint position):
	std::map<char,int>::iterator std_it = std_c0.begin();
	ft::map<char,int>::iterator ft_it = ft_c0.begin();
	std_c0.insert (std_it, std::pair<char,int>('b',300));  // max efficiency inserting
	std_c0.insert (std_it, std::pair<char,int>('c',400));  // no max efficiency inserting
	ft_c0.insert (ft_it, ft::pair<char,int>('b',300));  // max efficiency inserting
	ft_c0.insert (ft_it, ft::pair<char,int>('c',400));  // no max efficiency inserting
	testMap<char, int>(ft_c0, std_c0, NOPRINT);

	std::cout << HEADER_TITLE << "[ Insert with range ]" << RESET_COLOR << std::endl;
	// third insert function version (range insertion):
	std::map<char,int> std_anothermap;
	ft::map<char,int> ft_anothermap;
	std_anothermap.insert(std_c0.begin(),std_c0.end());
	ft_anothermap.insert(ft_c0.begin(),ft_c0.end());
	testMap<char, int>(ft_anothermap, std_anothermap, NOPRINT);
}

void
testBracketsInsert( void )	{

	{
		std::cout << HEADER_TITLE << "[ Insert with brackets ]" << RESET_COLOR << std::endl;
		std::map<char,int> 				std_c0;
		ft::map<char,int> 				ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];
		testMap<char, int>(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Insert with brackets and example Class ]" << RESET_COLOR << std::endl;
		std::map<char,exampleClass> 				std_c0;
		ft::map<char,exampleClass> 					ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];
		try {
			testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
		}
		catch (std::exception& e)	{
			std::cout << "Example Class has a default value of 42." << std::endl;
			throw failedTest();
		}
	}
}

void
testBasicErase( void )	{

		std::map<char,exampleClass> 				std_c0;
		ft::map<char,exampleClass> 					ft_c0;

		// insert some values:
		std_c0['a']=10;
		std_c0['b']=20;
		std_c0['c']=30;
		std_c0['d']=40;
		std_c0['e']=50;
		std_c0['f']=60;
		std_c0['g'];

		ft_c0['a']=10;
		ft_c0['b']=20;
		ft_c0['c']=30;
		ft_c0['d']=40;
		ft_c0['e']=50;
		ft_c0['f']=60;
		ft_c0['g'];

		std::map<char,exampleClass>::iterator		std_it = std_c0.begin();
		ft::map<char,exampleClass>::iterator		ft_it = ft_c0.begin();
		std::map<char,exampleClass>::iterator		std_ite = std_c0.end();
		ft::map<char,exampleClass>::iterator		ft_ite = ft_c0.end();

		std::cout << HEADER_TITLE << "[ Erase with position argument ]" << RESET_COLOR << std::endl;
		std_c0.erase(std_it);
		ft_c0.erase(ft_it);
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
		testBool( (--std_ite)->first == (--ft_ite)->first , __LINE__);
		std_ite++;
		ft_ite++;
		std::cout << HEADER_TITLE << "[ Erase with key argument ]" << RESET_COLOR << std::endl;
		std_c0.erase('c');
		ft_c0.erase('c');
		std_c0.erase('g');
		ft_c0.erase('g');
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);

		std::cout << HEADER_TITLE << "[ Erase with range argument ]" << RESET_COLOR << std::endl;
		std_it = std_c0.begin();
		ft_it = ft_c0.begin();
		std_c0.erase(std_it,std_ite);
		ft_c0.erase(ft_it, ft_ite);
		testMap<char, exampleClass>(ft_c0, std_c0, NOPRINT);
}

int
test_map_insert_erase( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;

		std::cout << TITLE << "[ INSERT ]" << RESET_COLOR << std::endl;
		testBasicInsertMemberFunction();
		testBracketsInsert();
		testCppRefCode();

		std::cout << TITLE << "[ ERASE ]" << RESET_COLOR << std::endl;
		testBasicErase();

		return (0);
}
