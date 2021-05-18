/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map_nonmember_swap.cpp                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:27 by bvalette          #+#    #+#             */
/*   Updated: 2021/02/22 16:01:29 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_map.hpp"

void
test_basic_swap(  ft::map<int , int>& ft_c0, ft::map<int , int>& ft_c1, std::map<int , int>& std_c0, std::map<int , int>& std_c1  )	{


		ft::map<int, int>::iterator			ft_it0 = ft_c0.begin();
		ft::map<int, int>::iterator			ft_it1 = ft_c1.begin();
		std::map<int, int>::iterator		std_it0 = std_c0.begin();
		std::map<int, int>::iterator		std_it1 = std_c1.begin();

		std::cout << SUBTITLE << "[ swap 2 maps ]" << RESET_COLOR << std::endl;
		ft::swap(ft_c0, ft_c1);
		std::swap(std_c0, std_c1);
		testMap(ft_c0, std_c0, NOPRINT, "Test map0");
		testMap(ft_c1, std_c1, NOPRINT, "Test map1");

		std::cout << SUBTITLE << "[ test if iterator stayed valid while pointing to new values ]" << RESET_COLOR << std::endl;
		testBool(&(*ft_it0) == &(*ft_c1.begin()), __LINE__);
		testBool(&(*ft_it1) == &(*ft_c0.begin()), __LINE__);
		testBool(&(*std_it0) == &(*std_c1.begin()), __LINE__);
		testBool(&(*std_it1) == &(*std_c0.begin()), __LINE__);
}

int
test_map_nonmember_swap( void )	{

	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	{
		std::cout << SUBTITLE << "[ Instanciate map0 with vector values ]" << RESET_COLOR << std::endl;
		std::vector<int>	val_0(100, 42);
		// std::vector<int>	val_0(100, 42);
		// should be iterator to a pair
		std::map<int, int>	std_c0(val_0.begin(), val_0.end());
		ft::map<int, int>	ft_c0(val_0.begin(), val_0.end());
		testMap(ft_c0, std_c0, NOPRINT);


		std::cout << SUBTITLE << "[ Instanciate map1 ]" << RESET_COLOR << std::endl;
		ft::map<int, int>	ft_c1;
		std::map<int, int>	std_c1;
		testMap(ft_c1, std_c1, NOPRINT);

		std::cout << SUBTITLE << "[ Instanciate map2 with another vector values ]" << RESET_COLOR << std::endl;
		std::vector<int>	val_1(1, 42);
		ft::map<int, int>	ft_c2(val_1.begin(), val_1.end());
		std::map<int, int>	std_c2(val_1.begin(), val_1.end());
		testMap(ft_c0, std_c0, NOPRINT);

		std::cout << SUBTITLE << "[ Instanciate map3 empty then insert with insert function ]" << RESET_COLOR << std::endl;
		ft::map<int, int>	ft_c3;
		std::map<int, int>	std_c3;
		ft_c0.insert(ft::make_pair(42, 21));
		std_c0.insert(std::make_pair(42, 21));
		testMap(ft_c0, std_c0, NOPRINT);

		// test_basic_swap(ft_c0, ft_c1, std_c0, std_c1);
		// test_basic_swap(ft_c1, ft_c2, std_c1, std_c2);
		// test_basic_swap(ft_c3, ft_c2, std_c3, std_c2);
		// test_basic_swap(ft_c2, ft_c2, std_c2, std_c2);

	}
	return (0);
}
