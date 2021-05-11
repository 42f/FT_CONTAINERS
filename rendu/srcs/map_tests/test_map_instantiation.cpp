/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_instantiation.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:31 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 12:17:25 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_map.hpp"

int
test_map_instantiation( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << TITLE << "~~~~ To see constructor calls, compile with " << RESET_COLOR << "-> make debug_mode=1 re f "<< std::endl;

		std::map<int, float>	std_c0;
		// std::pair<std::map<int, float>::iterator, bool> ret = std_c0.insert(std::pair<int, float>(42, 101));

		// std::cout << "ret c: " << ret.first->first << std::endl;

		ft::map<int, float>	ft_c0;

		// ft::pair<const int, float>	ft_p0( 3, 1 );
		// ft::pair<const int, float>	ft_p1( 2, 2 );
		// ft::pair<const int, float>	ft_p2( -1, 3 );
		// ft::pair<const int, float>	ft_p3( 5, 4 );
		// ft::pair<const int, float>	ft_p4( -3, 5 );

		// ft_c0.addNode(ft_p0);
		// ft_c0.addNode(ft_p1);
		// ft_c0.addNode(ft_p2);
		// ft_c0.addNode(ft_p3);
		// ft_c0.addNode(ft_p4);

		// std_c0[1] = 24;
		// std_c0[2] = 25;
		// std_c0[3] = 26;

		// std::map<const int, float>::iterator	itb_std = std_c0.begin();
		// std::map<const int, float>::iterator	ite_std = std_c0.end();

		// std::cout << "STD begin: first  " << itb_std->first << std::endl;
		// std::cout << "STD begin: second " << itb_std->second << std::endl;
		// std::cout << "STD end  : first  " << ite_std->first << std::endl;
		// std::cout << "STD end  : second " << ite_std->second << std::endl;

		// ft::map<const int, float>::iterator	itb_ft = ft_c0.begin();
		// std::cout << "FT begin: first  " << itb_ft->first << std::endl;
		// std::cout << "FT begin: second " << itb_ft->second << std::endl;
		// std::cout << "FT end  : first  " << ite_ft->first << std::endl;
		// std::cout << "FT end  : second " << ite_ft->second << std::endl;


		// std::cout << "FT:  first  " << it->first << std::endl;
		// std::cout << "FT:  second " << it->second << std::endl;
		// ft_c0.debugPrintTree();
		// std::cout << "test operator [3]" << ft_c0[3];
		// ft_c0[3] = 99;
		// std_c0[1];
		// std::cout << "1 ? " << std_c0[1] << std::endl;
		// std_c0[1] = 42;
		// std::cout << "1 ? " << std_c0[1] << std::endl;
		// std_c0[20] = 2;
		// std_c0[18] = 99;
		// std::map
		// std::cout << "test operator [3]" << ft_c0[3];
		// std::cout << "test operator [2]" << ft_c0[2];
		// std::cout << "test operator [-1]" << ft_c0[-1];
		// std::cout << "test operator [5]" << ft_c0[5];
		// std::cout << "test operator [-3]" << ft_c0[-3];
		// ft_c0.insertNode(ft_p0);
		// ft_c0.insertNode(ft_p1);

		/*
	{









		std::cout << SUBTITLE << "[ DEFAULT CONSTRUCTOR ]" << RESET_COLOR << std::endl;
		{
			ft::map<std::string>	ft_c0;
			std::map<std::string>	std_c0;
			testMap(ft_c0, std_c0, NOPRINT);
			ft::map<float>		ft_c1;
			std::map<float>	std_c1;
			testMap(ft_c1, std_c1, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(5, 123);
			std::map<int>	std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR with value explicitly casted ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(static_cast<size_t>(5),123);
			std::map<int>	std_c0(static_cast<size_t>(5),123);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>	ft_c0(5);
			std::map<int>	std_c0(5);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ FILL CONSTRUCTOR without value and with classExample which has a default value ]" << RESET_COLOR << std::endl;
		{
			ft::map<exampleClass>	ft_c0(5);
			std::map<exampleClass>	std_c0(5);
			testMap(ft_c0, std_c0, NOPRINT);
		}
		std::cout << SUBTITLE << "[ RANGE CONSTRUCTOR test: map0 with fill and map1 with range ctor from map0 iterators ]" << RESET_COLOR << std::endl;
		{
			ft::map<int>		ft_c0(5, 123);
			std::map<int>	std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);
			std::cout << SUBTITLE << "->>\t\t[ RANGE CONSTRUCTOR with begin and ++begin as argument ]" << RESET_COLOR << std::endl;
			ft::map<int>		ft_c1(ft_c0.begin(), ++ft_c0.begin());
			std::map<int>	std_c1(std_c0.begin(), ++std_c0.begin());
			testMap(ft_c1, std_c1, NOPRINT);

		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from map with 5 elements]" << RESET_COLOR << std::endl;
		{
			ft::map<int>			ft_c0(5, 123);
			std::map<int>		std_c0(5, 123);
			testMap(ft_c0, std_c0, NOPRINT);

			ft::map<int>			ft_c1(ft_c0);
			std::map<int>		std_c1(std_c0);
			testMap(ft_c1, std_c1, NOPRINT);

			std::cout << SUBTITLE << "[ check if begin points to a new elements ]" << RESET_COLOR << std::endl;
			testBool(&(*ft_c0.begin()) != &(*ft_c1.begin()), __LINE__);
			testBool(&(*std_c0.begin()) != &(*std_c1.begin()), __LINE__);
		}
		std::cout << SUBTITLE << "[ COPY CONSTRUCTOR from map with no elements]" << RESET_COLOR << std::endl;
		{
			ft::map<int>		ft_c0;
			std::map<int>	std_c0;

			ft::map<int>		ft_c1(ft_c0);
			std::map<int>	std_c1(std_c0);
			testMap(ft_c0, std_c0, NOPRINT);
			testMap(ft_c1, std_c1, NOPRINT);
		}
	}
	*/
	return (0);
}
