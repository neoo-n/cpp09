#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error : could not open file." << std::endl;
		return (-1);
	}
	try
	{
		std::string	file_name;
		file_name = "data.csv";
		BitcoinExchange	be(file_name);
		be.computing(av[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return (-2);
	}
	return (0);
}