#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		std::cerr << "Error : it needs argument(s)" << std::endl;
		return (-1);
	}
	try
	{
		PmergeMe	pm_vect(ac, av);
		pm_vect.sorting();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-2);
	}
	return (0);
}