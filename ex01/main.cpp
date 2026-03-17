#include "RPN.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (-1);
	}
	try
	{
		RPN	rpn;
		rpn.computing(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-2);
	}
	return (0);
}