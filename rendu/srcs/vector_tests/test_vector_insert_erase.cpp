/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_insert_erase.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:50:19 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/21 09:45:51 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_insert_erase( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "[ Instanciate vector of 4 strings ]" << RESET_COLOR << std::endl;
		ft::vector<std::string>		ft_c0(4, "___");
		std::vector<std::string>	std_c0(4, "___");
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert with insert(iterator, value) ]" << RESET_COLOR << std::endl;

		ft_c0.insert(ft_c0.begin(), "A");
		std_c0.insert(std_c0.begin(), "A");
		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin(), "B");
		std_c0.insert(std_c0.begin(), "B");
		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(++ft_c0.begin(), "42");
		std_c0.insert(++std_c0.begin(), "42");
		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(--ft_c0.end(), "The End...");
		std_c0.insert(--std_c0.end(), "The End...");
		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.end(), "End...");
		std_c0.insert(std_c0.end(), "End...");
		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.insert(ft_c0.begin() + ft_c0.size() / 2, "middle...");
		std_c0.insert(std_c0.begin() + std_c0.size() / 2, "middle...");
		testVector(ft_c0, std_c0, NOPRINT);


		std::cout << SUBTITLE << "[ test return of insert function ]" << RESET_COLOR << std::endl;
		testBool(*(ft_c0.insert(++ft_c0.begin(), "Return_this")) == *(std_c0.insert(++std_c0.begin(), "Return_this")), __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty vector ]" << RESET_COLOR << std::endl;
		ft::vector<std::string>		ft_c0;
		std::vector<std::string>	std_c0;
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert at begin() and check return ]" << RESET_COLOR << std::endl;

		testBool(*(ft_c0.insert(ft_c0.begin(), "Return_this")) == *(std_c0.insert(std_c0.begin(), "Return_this")), __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
	}
	{
		std::cout << HEADER_TITLE << "[ Instanciate empty vector ]" << RESET_COLOR << std::endl;
		ft::vector<std::string>		ft_c0;
		std::vector<std::string>	std_c0;
		testVector(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Insert at end() and check return ]" << RESET_COLOR << std::endl;

		testBool(*(ft_c0.insert(ft_c0.end(), "Return_this")) == *(std_c0.insert(std_c0.end(), "Return_this")), __LINE__);
		testVector(ft_c0, std_c0, NOPRINT);
	}



		// ft_c0.insert(--ft_c0.end(), "Bye!");
		// ft_c0.insert(ft_c0.end(), 5, val);
		// ft_c0.push_front("the Begining...");
		// ft_c0.push_back("the End...");

		// std_c0.insert(--std_c0.end(), "Bye!");
		// std_c0.insert(std_c0.end(), 5, val);
		// std_c0.push_front("the Begining...");
		// std_c0.push_back("the End...");


		// ft::vector<std::string>	ft_c1;
		// std::vector<std::string>	std_c1;

		// std::cout << SUBTITLE << "[ Insert with insert(iterator, iterator, iterator) ]" << RESET_COLOR << std::endl;
		// ft_c1.insert(ft_c1.begin(), ft_c0.begin(), ft_c0.end());
		// std_c1.insert(std_c1.begin(), std_c0.begin(), std_c0.end());

		// testVector(ft_c1, std_c1, NOPRINT);

		// std::cout << SUBTITLE << "[ Erase with erase(iterator) ]" << RESET_COLOR << std::endl;
		// for (int i = 0; i < 3; i++)
		// {
		// 	std::cout << "return ft = " << &(*ft_c1.erase(--ft_c1.end())) << std::endl;
		// 	std::cout << "return std= " << &(*std_c1.erase(--std_c1.end())) << std::endl;
		// }

		// testVector(ft_c1, std_c1, NOPRINT);
		// std::cout << SUBTITLE << "[ Erase with erase(iterator, iterator) ]" << RESET_COLOR << std::endl;
		// std::cout << "return ft  = " << &(*ft_c1.erase(ft_c1.begin(), --ft_c1.end())) << std::endl;
		// std::cout << "return std = " << &(*std_c1.erase(std_c1.begin(), --std_c1.end())) << std::endl;

		// testVector(ft_c1, std_c1, NOPRINT);
		// ft_c1.erase(ft_c1.begin(), ft_c1.end());
		// std_c1.erase(std_c1.begin(), std_c1.end());
		// testVector(ft_c1, std_c1, NOPRINT);
	return (0);
}
