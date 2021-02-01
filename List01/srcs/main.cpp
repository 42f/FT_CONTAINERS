#include <List.hpp>

int		main( void )	{

	ft::List<int>	lst(8, 0);

	(void)lst;
	std::cout << lst << std::endl;

	ft::List<int>::iterator	it = lst.front();

(void)it;
std::cout << &it << " " << *it << std::endl;
it++;
std::cout << &it << " " << *it << std::endl;
	// std::cout << it << std::endl;

	return (0);
}
