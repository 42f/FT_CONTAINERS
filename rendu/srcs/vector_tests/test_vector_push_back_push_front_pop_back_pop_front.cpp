/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_push_back_push_front_pop_back_p        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:18 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/20 08:31:45 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester_vector.hpp"

int
test_vector_push_back_push_front_pop_back_pop_front( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::vector<std::string>	ft_c0;
		std::vector<std::string>	std_c0;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ft_c0.push_front("the Begining...");
		ft_c0.push_back("the End...");
		ft_c0.push_back("the End...");

		std_c0.push_front("the Begining...");
		std_c0.push_back("the End...");
		std_c0.push_back("the End...");

		testVector(ft_c0, std_c0, NOPRINT);

		ft_c0.pop_front();
		ft_c0.pop_back();

		std_c0.pop_front();
		std_c0.pop_back();

		testVector(ft_c0, std_c0, NOPRINT);
		ft_c0.pop_front();

		std_c0.pop_front();

		testVector(ft_c0, std_c0, NOPRINT);

	}
	return (0);
}