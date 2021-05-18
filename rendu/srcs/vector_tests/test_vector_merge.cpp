/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector_merge.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvalette <bvalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 09:52:42 by bvalette          #+#    #+#             */
/*   Updated: 2021/05/18 09:50:28 by bvalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./tester/bvaletteTester_vector.hpp"


int
test_vector_merge( void )	{
	std::cout << TITLE << "~~~~~~~~~~~ " << __func__ << " with ints ~~~~~~~~~~~" << RESET_COLOR << std::endl;
	std::cout << HEADER_TITLE << "ASCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>		std_c0;
		ft::vector<int>		ft_c1;
		std::vector<int>		std_c1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " ASCENDING even values in vector 0 and odd values in vector 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = 0; i < testSize * 2; i++)	{
			if (i % 2 == 0)	{
				ft_c0.push_back(i);
				std_c0.push_back(i);
			}
			else	{
				ft_c1.push_back(i);
				std_c1.push_back(i);
			}
		}
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the vector into itself ]" << RESET_COLOR << std::endl;
		ft_c0.merge(ft_c0, greater_than);
		std_c0.merge(std_c0, greater_than);
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the vector 1 into vector 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ft_c0.merge(ft_c1, greater_than);
		std_c0.merge(std_c1, greater_than);
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "DESCENDING ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>		std_c0;
		ft::vector<int>		ft_c1;
		std::vector<int>		std_c1;
		size_t				testSize = 10;

		std::cout << SUBTITLE << "[ pushback " << testSize << " DESCENDING even values in vector 0 and odd values in vector 1 ]" << RESET_COLOR << std::endl;

		for (size_t i = testSize * 2; i > 0 ; i--)	{
			if (i % 2 == 0)	{
				ft_c0.push_back(i);
				std_c0.push_back(i);
			}
			else	{
				ft_c1.push_back(i);
				std_c1.push_back(i);
			}
		}

		ft_c1.push_back(1000);
		std_c1.push_back(1000);

		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the vector 1 into vector 0 with smaller_than Compare]" << RESET_COLOR << std::endl;
		ft_c0.merge(ft_c1, smaller_than);
		std_c0.merge(std_c1, smaller_than);
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER with merge(2)" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>		std_c0;
		ft::vector<int>		ft_c1;
		std::vector<int>		std_c1;
		size_t				testSize = 1000000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into vector 0 and vector 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&std_c0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ft_c0.push_back(val);
			std_c0.push_back(val);
			val = rand() % 40;
			ft_c1.push_back(val);
			std_c1.push_back(val);
		}
		ft_c0.push_back(42);
		std_c0.push_back(42);
		ft_c0.push_back(42);
		std_c0.push_back(42);

		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the vector 1 into vector 0 with greater_than Compare]" << RESET_COLOR << std::endl;
		ft_c0.merge(ft_c1, greater_than);
		std_c0.merge(std_c1, greater_than);
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
	}
	std::cout << HEADER_TITLE << "RANDOM ORDER - with merge(1)" << RESET_COLOR << std::endl;
	{
		ft::vector<int>		ft_c0;
		std::vector<int>		std_c0;
		ft::vector<int>		ft_c1;
		std::vector<int>		std_c1;
		size_t				testSize = 1000;

		std::cout << SUBTITLE << "[ pushback " << testSize << " random values into vector 0 and vector 1 (different values)]" << RESET_COLOR << std::endl;

		srand(reinterpret_cast<long unsigned int>(&std_c0));
		for (size_t i = 0; i < testSize; i++)	{
			int val = rand() % 20;
			ft_c0.push_back(val);
			std_c0.push_back(val);
			val = rand() % 40;
			ft_c1.push_back(val);
			std_c1.push_back(val);
		}
		ft_c0.push_back(42);
		std_c0.push_back(42);
		ft_c0.push_back(42);
		std_c0.push_back(42);

		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
		std::cout << SUBTITLE << "[ test to merge the vector 1 into vector 0 with no compare argument (merge(1)) ]" << RESET_COLOR << std::endl;
		ft_c0.merge(ft_c1);
		std_c0.merge(std_c1);
		testVector(ft_c0, std_c0, NOPRINT);
		testVector(ft_c1, std_c1, NOPRINT);
	}
	return (0);
}
