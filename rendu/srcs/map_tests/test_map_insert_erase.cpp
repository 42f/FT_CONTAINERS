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

#include "bvaletteTester_map.hpp"

void
testInsert ( void )	{
		std::cout << SUBTITLE << "[ Insert with two different Compare functions]" << RESET_COLOR << std::endl;
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

			testMap<char, int, std::greater<char> >(ft_first_greater, std_first_greater, PRINT);
			testMap<char, int>(ft_c0, std_c0, PRINT);
		}
	{
		std::cout << HEADER_TITLE << "[ Instanciate map of 4 strings ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0(4, "___");
		std::map<std::string>	std_c0(4, "___");
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, value) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), "A");
		std_c0.insert(std_c0.begin(), "A");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin(), "B");
		std_c0.insert(std_c0.begin(), "B");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(++ft_c0.begin(), "42");
		std_c0.insert(++std_c0.begin(), "42");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(--ft_c0.end(), "The End...");
		std_c0.insert(--std_c0.end(), "The End...");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.end(), "End...");
		std_c0.insert(std_c0.end(), "End...");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, "middle...");
		std_c0.insert(std_c0.begin() + std_c0.size() / 2, "middle...");
		testMap(ft_c0, std_c0, NOPRINT);


		std::cout << SUBTITLE << "[ test return of insert function ]" << RESET_COLOR << std::endl;
		testBool(*(ft_c0.insert(++ft_c0.begin(), "Return_this")) == *(std_c0.insert(++std_c0.begin(), "Return_this")), __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert at begin() and check return ]" << RESET_COLOR << std::endl;

		testBool(*(ft_c0.insert(ft_c0.begin(), "Return_this")) == *(std_c0.insert(std_c0.begin(), "Return_this")), __LINE__);
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert at end() and check return ]" << RESET_COLOR << std::endl;

		testBool(*(ft_c0.insert(ft_c0.end(), "Return_this")) == *(std_c0.insert(std_c0.end(), "Return_this")), __LINE__);
		testMap(ft_c0, std_c0, NOPRINT);
	}

}
void
testInsert ( size_t n )	{
	{
		std::cout << HEADER_TITLE << "[ Instanciate map of 4 strings ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0(4, "___");
		std::map<std::string>	std_c0(4, "___");
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, " << n <<",value) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), n, "A");
		std_c0.insert(std_c0.begin(), n, "A");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin(), n, "B");
		std_c0.insert(std_c0.begin(), n, "B");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(++ft_c0.begin(), n, "42");
		std_c0.insert(++std_c0.begin(), n, "42");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(--ft_c0.end(), "n, The End...");
		std_c0.insert(--std_c0.end(), "n, The End...");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.end(), n, "End...");
		std_c0.insert(std_c0.end(), n, "End...");
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, n, "middle...");
		std_c0.insert(std_c0.begin() + std_c0.size() / 2, n, "middle...");
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert " << n << " elements at begin() ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), n, "Return_this");
		std_c0.insert(std_c0.begin(), n, "Return_this");
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert " << n << " elements at end() ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.end(), n, "Return_this");
		std_c0.insert(std_c0.end(), n, "Return_this");
		testMap(ft_c0, std_c0, NOPRINT);
	}

}
void
testInsert ( ft::map<std::string>::iterator ft_it,
			ft::map<std::string>::iterator ft_ite,
			std::map<std::string>::iterator std_it,
			std::map<std::string>::iterator std_ite)	{

	{
		std::cout << HEADER_TITLE << "[ Instanciate map of 4 strings ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0(4, "___");
		std::map<std::string>	std_c0(4, "___");
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), ft_it, ft_ite);
		std_c0.insert(std_c0.begin(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin(), ft_it, ft_ite);
		std_c0.insert(std_c0.begin(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(++ft_c0.begin(), ft_it, ft_ite);
		std_c0.insert(++std_c0.begin(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(--ft_c0.end(), ft_it, ft_ite);
		std_c0.insert(--std_c0.end(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.end(), ft_it, ft_ite);
		std_c0.insert(std_c0.end(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, ft_it, ft_ite);
		std_c0.insert(std_c0.begin() + std_c0.size() / 2, std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), ft_it, ft_ite);
		std_c0.insert(std_c0.begin(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty map ]" << RESET_COLOR << std::endl;
		ft::map<std::string>		ft_c0;
		std::map<std::string>	std_c0;
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.end(), ft_it, ft_ite);
		std_c0.insert(std_c0.end(), std_it, std_ite);
		testMap(ft_c0, std_c0, NOPRINT);
	}

}

void
testErase (void )	{
		std::cout << TITLE << "[ Erase ]" << RESET_COLOR << std::endl;
		size_t	testSize = 10;
		std::cout << HEADER_TITLE << "[ Instanciate map with "<< testSize <<" \"helloWorld\" ]" << RESET_COLOR << std::endl;

		ft::map<std::string>	ft_c0(testSize, "helloWorld");
		std::map<std::string>	std_c0(testSize, "helloWorld");

		for (size_t i = 0; i < 2; i++)	{
			ft_c0.push_back("THE END");
			std_c0.push_back("THE END");
		}
		for (size_t i = 0; i < 1; i++)	{
			ft_c0.insert(ft_c0.begin(), "THE BEGINING");
			std_c0.insert(std_c0.begin(), "THE BEGINING");
		}
		testMap(ft_c0, std_c0, NOPRINT);

		testSize = std_c0.size();
		std::cout << SUBTITLE << "[ Loop Erase with erase(iterator) ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < testSize / 2; i++)
		{

			ft::map<std::string>::iterator	ftIt;
			std::map<std::string>::iterator	stdIt;
			if (i == 1)	{
				std::cout << SUBTITLE << "[ Erase with erase(iterator) size() / 2 ]" << RESET_COLOR << std::endl;
				ftIt = ft_c0.begin() + (ft_c0.size() / 2);
				stdIt = std_c0.begin() + (std_c0.size() / 2);
			}
			else if (i % 2 == 0)	{
				std::cout << SUBTITLE << "[ Erase with erase(iterator) --end() ]" << RESET_COLOR << std::endl;
				ftIt = --ft_c0.end();
				stdIt = --std_c0.end();
			}
			else	{
				std::cout << SUBTITLE << "[ Erase with erase(iterator) begin() ]" << RESET_COLOR << std::endl;
				ftIt = ft_c0.begin();
				stdIt = std_c0.begin();
			}

			std::string * ft_ptr = &(*ftIt);
			std::string * std_ptr = &(*stdIt);

			std::string * ret_ft_ptr = &(*ft_c0.erase(ftIt));
			std::string * ret_std_ptr = &(*std_c0.erase(stdIt));

			if (ft_ptr != ret_ft_ptr || std_ptr != ret_std_ptr)	{
				std::cout << "ft\tPtr expected = " << ft_ptr << ", got = " << ret_ft_ptr << std::endl;
				std::cout << "std\tPtr expected = " << std_ptr << ", got = " << ret_std_ptr << std::endl;
			}
			testMap(ft_c0, std_c0, NOPRINT);
			testBool(ft_ptr == ret_ft_ptr && std_ptr == ret_std_ptr, __LINE__, i);
		}
}

void
testEraseRange(
			ft::map<std::string> & ft_c0,
			std::map<std::string> & std_c0,
			ft::map<std::string>::iterator ftIt,
			ft::map<std::string>::iterator ftIte,
			std::map<std::string>::iterator stdIt,
			std::map<std::string>::iterator stdIte)	{

			std::string * ft_ptr = &(*ftIt);
			std::string * std_ptr = &(*stdIt);

			std::string * ret_ft_ptr = &(*ft_c0.erase(ftIt, ftIte));
			std::string * ret_std_ptr = &(*std_c0.erase(stdIt, stdIte));

			if (ft_ptr != ret_ft_ptr || std_ptr != ret_std_ptr)	{
				std::cout << "ft\tPtr expected = " << ft_ptr << ", got = " << ret_ft_ptr << std::endl;
				std::cout << "std\tPtr expected = " << std_ptr << ", got = " << ret_std_ptr << std::endl;
			}
			testMap(ft_c0, std_c0, NOPRINT);
			testBool(ft_ptr == ret_ft_ptr && std_ptr == ret_std_ptr, __LINE__);
}

int
test_map_insert_erase( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;

		std::cout << TITLE << "[ INSERT ]" << RESET_COLOR << std::endl;
		testInsert();
		testInsert(1);
		testInsert(3);
		testInsert(100000);
		{
			ft::map<std::string>		ft_c0(20, "XX");
			std::map<std::string>	std_c0(20, "XX");

			testInsert(ft_c0.begin(), ft_c0.end(), std_c0.begin(), std_c0.end());
			testInsert(++ft_c0.begin(), --ft_c0.end(), ++std_c0.begin(), --std_c0.end());
		}

		testErase();

		{
			size_t	testSize = 40;
			std::cout << HEADER_TITLE << "[ Instanciate map with "<< testSize <<" \"XX\" ]" << RESET_COLOR << std::endl;
			ft::map<std::string>		ft_c0(testSize, "XX");
			std::map<std::string>	std_c0(testSize, "XX");
			testMap(ft_c0, std_c0, NOPRINT);
			std::cout << SUBTITLE << "[ Erase with various erase(iterator, iterator) ]" << RESET_COLOR << std::endl;

			ft::map<std::string>::iterator	ftIt = ft_c0.begin();
			ft::map<std::string>::iterator	ftIte = ft_c0.end() - ft_c0.size() / 2;
			std::map<std::string>::iterator	stdIt = std_c0.begin();
			std::map<std::string>::iterator	stdIte = std_c0.end() - std_c0.size() / 2;

			testEraseRange(ft_c0, std_c0, ftIt, ftIte, stdIt, stdIte);

			ftIt = ft_c0.begin();
			ftIte = ft_c0.begin() + 1;
			stdIt = std_c0.begin();
			stdIte = std_c0.begin() + 1;
			testEraseRange(ft_c0, std_c0, ftIt, ftIte, stdIt, stdIte);


			ftIt = ft_c0.end() - 5;
			ftIte = ft_c0.end() - 0;
			stdIt = std_c0.end() - 5;
			stdIte = std_c0.end() - 0;
			testEraseRange(ft_c0, std_c0, ftIt, ftIte, stdIt, stdIte);


			ftIt = ft_c0.begin() + 4;
			ftIte = ft_c0.begin() + 11;
			stdIt = std_c0.begin() + 4;
			stdIte = std_c0.begin() + 11;
			testEraseRange(ft_c0, std_c0, ftIt, ftIte, stdIt, stdIte);

			ftIt = ft_c0.begin();
			ftIte = ft_c0.end();
			stdIt = std_c0.begin();
			stdIte = std_c0.end();
			testEraseRange(ft_c0, std_c0, ftIt, ftIte, stdIt, stdIte);
		}
	return (0);
}
