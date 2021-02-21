/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_push_back_pop_back.cpp                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:18 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 17:28:35 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_push_back_pop_back( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		size_t	vctSize = 5;
		ft::vector<std::string>		ft_c0(vctSize, "The Begining...");
		std::vector<std::string>	std_c0(vctSize, "The Begining...");

		testVector(ft_c0, std_c0, PRINT);

		size_t	testSize = ft_c0.capacity() + 10;
		std::cout << SUBTITLE << "[ Push_back " << testSize << " times ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < testSize; i++)
		{
			ft_c0.push_back("the End...");
			std_c0.push_back("the End...");
		}
		testVector(ft_c0, std_c0, PRINT);

		// testSize += vctSize;
		// std::cout << SUBTITLE << "[ pop_back " << testSize << " times ]" << RESET_COLOR << std::endl;
		// for (size_t i = 0; i < testSize; i++)
		// {
		// 	ft_c0.pop_back();
		// 	std_c0.pop_back();
		// }
		// testVector(ft_c0, std_c0, PRINT);

	}
	return (0);
}
