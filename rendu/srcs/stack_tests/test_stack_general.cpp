/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stack_general.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 20:58:15 by bvalette          #+#    #+#             */
/*   Updated: 2021/06/07 22:04:20 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./list/list.hpp"
# include "./tester/bvaletteTester_stack.hpp"

int
test_stack_general( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << HEADER_TITLE << "Instanciation with no arguments" << RESET_COLOR << std::endl;
		ft::stack<int>		ft_c0;
		std::stack<int>		std_c0;

		std::cout << HEADER_TITLE << "Empty() on empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __LINE__);
		std::cout << HEADER_TITLE << "Size() on empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "Instanciation arguments for deque container" << RESET_COLOR << std::endl;
		ft::stack<int>		ft_c0(ft::deque<int>(10, 42));
		std::stack<int>		std_c0(std::deque<int>(10, 42));

		std::cout << HEADER_TITLE << "Empty() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __LINE__);
		std::cout << HEADER_TITLE << "Size() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __LINE__);
	}
	{
		std::cout << HEADER_TITLE << "Instanciation arguments for a map container" << RESET_COLOR << std::endl;
		ft::stack<int, ft::list<int>>		ft_c0(ft::list<int>(10, 42));
		std::stack<int, std::list<int>>		std_c0(std::list<int>(10, 42));

		std::cout << HEADER_TITLE << "Empty() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.empty() == std_c0.empty(), __LINE__);
		std::cout << HEADER_TITLE << "Size() on non empty container" << RESET_COLOR << std::endl;
		testBool(ft_c0.size() == std_c0.size(), __LINE__);
	}

	{
		std::cout << HEADER_TITLE << "Instanciation arguments for deque container" << RESET_COLOR << std::endl;
		ft::stack<int, ft::list<int> >		ft_c0(ft::list<int>(10, 42));
		std::stack<int, std::list<int> >		std_c0(std::list<int>(10, 42));
		ft::stack<int, ft::list<int> >		ft_c1(ft::list<int>(10, 21));
		std::stack<int, std::list<int> >		std_c1(std::list<int>(10, 21));

		std::cout << HEADER_TITLE << "Relational Operators" << RESET_COLOR << std::endl;
		std::cout << SUBTITLE<< "operator==" << RESET_COLOR << std::endl;
		testBool(ft_c0 == ft_c0 && std_c0 == std_c0, __LINE__);
		// std::cout << SUBTITLE<< "operator!=" << RESET_COLOR << std::endl;
		// testBool(ft_c0 != ft_c1 && std_c0 != std_c1, __LINE__);
	}

	return (0);

}
