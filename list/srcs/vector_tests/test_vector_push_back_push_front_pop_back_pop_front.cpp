/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_push_back_push_front_pop_back_p        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:18 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/17 09:52:19 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvaletteTester.hpp"

int
test_vector_push_back_push_front_pop_back_pop_front( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with std::string ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		ft::list<std::string>	ftl0;
		std::list<std::string>	stdl0;

		std::cout << SUBTITLE << "[ Insert with insert(iterator, size_t, value_type) ]" << RESET_COLOR << std::endl;
		ftl0.push_front("the Begining...");
		ftl0.push_back("the End...");
		ftl0.push_back("the End...");

		stdl0.push_front("the Begining...");
		stdl0.push_back("the End...");
		stdl0.push_back("the End...");

		testList(ftl0, stdl0, NOPRINT);

		ftl0.pop_front();
		ftl0.pop_back();

		stdl0.pop_front();
		stdl0.pop_back();

		testList(ftl0, stdl0, NOPRINT);
		ftl0.pop_front();

		stdl0.pop_front();

		testList(ftl0, stdl0, NOPRINT);

	}
	return (0);
}
