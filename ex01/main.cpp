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
		RPN	rpn(av[1]);
		rpn.computing();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-2);
	}
	return (0);
}