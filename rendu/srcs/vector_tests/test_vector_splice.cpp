/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_splice.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:51:13 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/19 14:22:40 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_splice( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with int ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ft_c0(8, 0);
		ft::list<int>	ft_c1(8, 1);
		std::list<int>	std_c0(8, 0);
		std::list<int>	std_c1(8, 1);

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);

		std::cout << SUBTITLE << "[ splice (entire list (1)) entire list 0 to begining of list 1 ]" << RESET_COLOR << std::endl;
		ft_c1.splice(ft_c1.begin(), ft_c0);
		std_c1.splice(std_c1.begin(), std_c0);
		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (entire list (1)) entire list 1 to end of list 0 ]" << RESET_COLOR << std::endl;
		ft_c0.splice(ft_c0.end(), ft_c1);
		std_c0.splice(std_c0.end(), std_c1);
		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);

		std::cout << SUBTITLE << "[ instanciate new empty list 3 and splice (entire list (1)) entire list 0 to end of list 3 ]" << RESET_COLOR << std::endl;
		ft::list<int>	ft_c3;
		std::list<int>	std_c3;
		ft_c3.splice(ft_c3.end(), ft_c0);
		std_c3.splice(std_c3.end(), std_c0);
		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		testList(ft_c3, std_c3,  NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ft_c0(5, "HelloWorld!");
		ft::list<std::string>	ft_c1(5, "bye!");
		std::list<std::string>	std_c0(5, "HelloWorld!");
		std::list<std::string>	std_c1(5, "bye!");

		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer second element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = ++ft_c0.begin();
		std::list<std::string>::iterator	std_itl0 = ++std_c0.begin();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ft_c1.splice(ft_c1.begin(), ft_c0, ft_itl0);
		std_c1.splice(std_c1.begin(), std_c0, std_itl0);

		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ft_c1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*std_c1.begin()),__LINE__);
		std::cout << SUBTITLE << "[ check if previously list 0 iterator does iterate on list 1 now ]" << RESET_COLOR << std::endl;
		testBool( *(++ft_itl0) == "bye!" , __LINE__);
		testBool( *(++std_itl0) == "bye!" , __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 5 HelloWorld, list 1 with 5 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ft_c0(5, "HelloWorld!");
		ft::list<std::string>	ft_c1(5, "bye!");
		std::list<std::string>	std_c0(5, "HelloWorld!");
		std::list<std::string>	std_c1(5, "bye!");

		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the LAST element of list 0 to the first position of list 1 ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = --ft_c0.end();
		std::list<std::string>::iterator	std_itl0 = --std_c0.end();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ft_c1.splice(ft_c1.begin(), ft_c0, ft_itl0);
		std_c1.splice(std_c1.begin(), std_c0, std_itl0);

		testList(ft_c0, std_c0, NOPRINT);
		testList(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ft_c1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*std_c1.begin()),__LINE__);

	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 1 HelloWorld, list 1 with 1 Bye! ]" << RESET_COLOR << std::endl;

		ft::list<std::string>	ft_c0(1, "HelloWorld!");
		ft::list<std::string>	ft_c1(1, "bye!");
		std::list<std::string>	std_c0(1, "HelloWorld!");
		std::list<std::string>	std_c1(1, "bye!");

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (single element(2) version):transfer the first (and only) element from list 0 to list 1 begin ]" << RESET_COLOR << std::endl;
		ft::list<std::string>::iterator		ft_itl0 = ft_c0.begin();
		std::list<std::string>::iterator	std_itl0 = std_c0.begin();

		void * ft_ptr_splicedElem = &(*ft_itl0);
		void * std_ptr_splicedElem = &(*std_itl0);

		ft_c1.splice(ft_c1.begin(), ft_c0, ft_itl0);
		std_c1.splice(std_c1.begin(), std_c0, std_itl0);

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);

		std::cout << SUBTITLE << "[ check the address of the spliced element, it should remain similar ]" << RESET_COLOR << std::endl;
		testBool( ft_ptr_splicedElem ==  &(*ft_c1.begin()),__LINE__);
		testBool( std_ptr_splicedElem ==  &(*std_c1.begin()),__LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ft_c0(8, 0);
		ft::list<int>	ft_c1(8, 1);
		std::list<int>	std_c0(8, 0);
		std::list<int>	std_c1(8, 1);

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version):transfer list 0 elements from begin to begin + 4 to list 1 ]" << RESET_COLOR << std::endl;
		ft::list<int>::iterator		ft_itl0 = ft_c0.begin();
		std::list<int>::iterator	std_itl0 = std_c0.begin();
		ft::list<int>::iterator		ft_it_4_l0 = ft_c0.begin();
		std::list<int>::iterator	std_it_4_l0 = std_c0.begin();
		for (int i = 0; i < 4; ++i)	{
			ft_it_4_l0++;
			std_it_4_l0++;
		}

		testList(ft_c0, std_c0,  NOPRINT, "before test on list 0");
		testList(ft_c1, std_c1,  NOPRINT, "before test on list 1");
		std::cout << SUBTITLE << "[ splice here ]" << RESET_COLOR << std::endl;
		ft_c1.splice(ft_c1.begin(), ft_c0, ft_itl0, ft_it_4_l0);
		std_c1.splice(std_c1.begin(), std_c0, std_itl0, std_it_4_l0);
		testList(ft_c0, std_c0,  NOPRINT, "test on list 0");
		testList(ft_c1, std_c1,  NOPRINT, "test on list 1");
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ft_c0(8, 0);
		ft::list<int>	ft_c1(8, 1);
		std::list<int>	std_c0(8, 0);
		std::list<int>	std_c1(8, 1);

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version): iterator begin of list 0 into list 1 until list 0 is empty ]" << RESET_COLOR << std::endl;

		while(ft_c0.empty() == false && std_c0.empty() == false)	{
			ft_c1.splice(ft_c1.begin(), ft_c0, ft_c0.begin());
			std_c1.splice(std_c1.begin(), std_c0, std_c0.begin());
			testList(ft_c0, std_c0,  NOPRINT);
			testList(ft_c1, std_c1,  NOPRINT);
		}
		std::cout << SUBTITLE << "[ check if ft list 0 AND std list 0 are both empty ]" << RESET_COLOR << std::endl;
		testBool( ft_c0.empty() == std_c0.empty());
		std::cout << SUBTITLE << "[ same opposite direction ( list 1 to list 0) ]" << RESET_COLOR << std::endl;

		while(ft_c1.empty() == false && std_c1.empty() == false)	{
			ft_c0.splice(ft_c0.begin(), ft_c1, ft_c1.begin());
			std_c0.splice(std_c0.begin(), std_c1, std_c1.begin());
			testList(ft_c0, std_c0,  NOPRINT);
			testList(ft_c1, std_c1,  NOPRINT);
		}
		std::cout << SUBTITLE << "[ check if ft list 1 AND std list 1 are both empty ]" << RESET_COLOR << std::endl;
		testBool( ft_c1.empty() == std_c1.empty());
	}
	{
		std::cout << HEADER_TITLE << "[ list 0 with 8 values '0', list 1 with 8 values '1' ]" << RESET_COLOR << std::endl;

		ft::list<int>	ft_c0(8, 0);
		ft::list<int>	ft_c1(8, 1);
		std::list<int>	std_c0(8, 0);
		std::list<int>	std_c1(8, 1);

		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
		std::cout << SUBTITLE << "[ splice (range(3) version): last element from list 0 to begining of list 1, back and forth 100 times]" << RESET_COLOR << std::endl;

		for (int i = 0; i < 100; i++)	{
			ft_c1.splice(ft_c1.begin(), ft_c0, --ft_c0.end());
			std_c1.splice(std_c1.begin(), std_c0, --std_c0.end());
			ft_c0.splice(ft_c0.begin(), ft_c1, ft_c1.begin());
			std_c0.splice(std_c0.begin(), std_c1, std_c1.begin());
		}
		testList(ft_c0, std_c0,  NOPRINT);
		testList(ft_c1, std_c1,  NOPRINT);
	}
	return (0);
}
