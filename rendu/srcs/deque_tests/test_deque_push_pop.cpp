/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_deque_push_pop.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:18 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/07 10:51:56 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_deque.hpp"

int
test_deque_push_pop( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		size_t	vctSize = 5;
		ft::deque<std::string>		ft_c0(vctSize, "The Begining...");
		std::deque<std::string>	std_c0(vctSize, "The Begining...");

		testDeque(ft_c0, std_c0, NOPRINT);

		size_t	testSize = ft_c0.capacity() + 5;
		std::cout << SUBTITLE << "[ Push_back " << testSize << " times ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < testSize; i++)
		{
			ft_c0.push_back("the End...");
			std_c0.push_back("the End...");
			testDeque(ft_c0, std_c0, NOPRINT);
		}

		ft_c0.push_back("_____");
		std_c0.push_back("_____");
		testDeque(ft_c0, std_c0, NOPRINT);
		testSize += vctSize + 1;
		std::cout << SUBTITLE << "[ pop_back " << testSize << " times ]" << RESET_COLOR << std::endl;
		for (size_t i = 0; i < testSize; i++)
		{
			std_c0.pop_back();
			ft_c0.pop_back();
			testDeque(ft_c0, std_c0, NOPRINT);
		}
	}
	return (0);
}
