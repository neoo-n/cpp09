#include "PmergeMe.hpp"

// CONSTRUCTOR & DESTRUCTOR
PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(int ac, char **av)
{
	this->_parsing(ac, av);
}

PmergeMe::PmergeMe(const PmergeMe &cpy)
{
	if (this != &cpy)
	{
		this->_values = cpy._values;
	}
}

PmergeMe::~PmergeMe()
{

}

PmergeMe	&PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		this->_values = obj._values;
	}
	return (*this);
}

//METHODS
//PRIVATE

bool	PmergeMe::_isDuplicate(int temp)
{
	for (size_t	i = 0; i < this->_values.size(); i++)
	{
		if (this->_values[i] == temp)
			return (true);
	}
	return (false);
}

void	PmergeMe::_parsing(int ac, char **av)
{
	int			temp;
	std::string	str_temp;

	for (int i = 1; i < ac; i++)
	{
		str_temp = av[i];
		if (str_temp.find_first_not_of("1234567890") != std::string::npos)
			throw std::invalid_argument("Error : invalid input");
		std::stringstream	ss(str_temp);
		ss >> temp;
		if (temp == 0)
			throw std::invalid_argument("Error : input has value zero");
		if (this->_isDuplicate(temp))
			throw std::invalid_argument("Error : invalid input, it's a duplicate");
		this->_values.push_back(temp);
	}
	// for (size_t i = 0; i < this->_values.size(); i++)
	// {
	// 	std::cout << this->_values[i] << " ";
	// }
}

// PUBLIC
void	PmergeMe::sorting_vect(std::vector<int>	list_to_sort)
{
	size_t				nb_val_list;
	size_t				half_nb;
	std::vector<int>	max_val;
	std::vector<int>	min_val;
	std::vector<int>	res;
	
	nb_val_list = list_to_sort.size();
	if (nb_val_list > 2)
	{
		half_nb = list_to_sort.size() / 2;
		for (size_t i = 0; i < half_nb; i++)
		{
			if (list_to_sort[i] < list_to_sort[i + 1])
			{
				min_val.push_back(list_to_sort[i]);
				max_val.push_back(list_to_sort[i + 1]);
			}
			else
			{
				min_val.push_back(list_to_sort[i + 1]);
				max_val.push_back(list_to_sort[i]);
			}
		}
		if (list_to_sort.size() % 2 == 1)
			min_val.push_back(list_to_sort[nb_val_list - 1])
	}
	else if (nb_val_list == 2)
	{
		if (list_to_sort[1] < list_to_sort[0])
			list_to_sort.swap()
	}
	
}