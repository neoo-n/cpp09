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
		for (size_t i = 0; i < cpy._elt.size(); i++)
		{
			pm *elt = new pm;
			elt->max = cpy._elt[i]->max;
			elt->lower = cpy._elt[i]->lower;
			this->_elt.push_back(elt);
		}
	}
}

PmergeMe::~PmergeMe()
{

}

PmergeMe	&PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		for (size_t i = 0; i < obj._elt.size(); i++)
		{
			pm *elt = new pm;
			elt->max = obj._elt[i]->max;
			elt->lower = obj._elt[i]->lower;
			this->_elt.push_back(elt);
		}
	}
	return (*this);
}

//METHODS
//PRIVATE

bool	PmergeMe::_isDuplicate(int temp)
{
	for (size_t	i = 0; i < this->_elt.size(); i++)
	{
		if (this->_elt[i]->max == temp)
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
		pm	*elt = new pm;
		elt->max = temp;
		this->_elt.push_back(elt);
	}
	for (size_t i = 0; i < this->_elt.size(); i++)
	{
		std::cout << this->_elt[i]->max<< " ";
	}
	std::cout << std::endl;
}

std::vector<pm *>	PmergeMe::_swaping(std::vector<pm *> v, size_t i1, size_t i2)
{
	std::vector<pm *>	res;
	size_t			size;

	size = v.size();
	for(size_t i = 0; i < size; i++)
	{
		if (i == i1)
			res.push_back(v[i2]);
		else if (i == i2)
			res.push_back(v[i1]);
		else
			res.push_back(v[i]);
	}
	return (res);
}

std::vector<int>	PmergeMe::_jacobstahl_compute(int size)
{
	std::vector<int>	res;
	int					val;
	int					prev;
	int					second_prev;
	bool				existing;
	int					sizeRes;

	second_prev = 0;
	prev = 1;
	val = 0;
	res.push_back(1);
	while (val > size)
  {
		existing = false;
		val = prev + 2 * second_prev;
		if (val < size)
		{
			res.push_back(val);
			for (int i = val - 1; i > 0; i--)
			{
				for (size_t j = 0; j < res.size(); j++)
				{
					if (res[j] == i)
					{
						existing = true;
						break ;
					}
				}
				if (existing)
					break ;
				else
					res.push_back(i);
			}
		}
	} 
	sizeRes = res.size();
	if (sizeRes < size)
		val = size;
	while (sizeRes < size)
	{
		res.push_back(val);
		val--;
		sizeRes++;
	}
	return (res);
}

int	PmergeMe::_binary_search(std::vector<pm *> v, pm *elt)
{
	std::vector<pm *>::iterator it;
	size_t						index_max;
	size_t						index_min;
	size_t						index_look;

	it = std::find(v.begin(), v.end(), elt);
	index_max = it - v.begin();
	if (index_max == 0)
		return (0);
	index_min = 0;
	index_look = (index_max - index_min) / 2;
	while (index_min + 1 == index_max)
	{
		if (v[index_look]->max < elt->max)
		{
			index_min = index_look;
			index_look += (index_max - index_min) / 2;
		}
		else
		{
			index_max = index_look;
			index_look -= (index_max - index_min) / 2;
		}
	}
	if (elt->max < v[index_min]->max)
		return (index_min);
	return (index_max);
}

// PUBLIC

std::vector<pm *>	PmergeMe::getElt() const
{
	return (this->_elt);
}

std::vector<pm *>	PmergeMe::sorting_vect(std::vector<pm *> list_to_sort)
{
	size_t				nb_val_list;
	size_t				half_nb;
	std::vector<pm *>	val;
	std::vector<pm *>	res;
	std::vector<pm *>	temp;
	std::vector<int>	jacobsthal_list;
	pm					*rest;

	rest = NULL;
	std::cout << "beginning ---------------------------------" << std::endl;
	nb_val_list = list_to_sort.size();
	if (nb_val_list > 2)
	{
		half_nb = list_to_sort.size() / 2;
		std::cout << "half : " << half_nb << std::endl;
		for (size_t i = 0; i < half_nb; i++)
		{
			if (list_to_sort[i * 2]->max < list_to_sort[i * 2 + 1]->max)
			{
				list_to_sort[i * 2 + 1]->lower.push_back(list_to_sort[i * 2]);
				val.push_back(list_to_sort[i * 2 + 1]);
			}
			else
			{
				list_to_sort[i * 2]->lower.push_back(list_to_sort[i * 2 + 1]);
				val.push_back(list_to_sort[i * 2]);
			}
		}
		if (nb_val_list % 2 == 1)
		{
			rest = new pm;
			rest = list_to_sort[nb_val_list - 1];
		}
		std::cout << "size val : " << val.size() << std::endl;
		for (size_t i = 0; i < val.size(); i++)
		{
			std::cout << "val : " << val[i]->max << " " << val[i]->lower.size() << std::endl;
		}
		temp = this->sorting_vect(val);
		std::cout << "size temp : " << temp.size() << std::endl;
		for (size_t i = 0; i < temp.size(); i++)
		{
			std::cout << temp[i]->max << " " << temp[i]->lower.size() << std::endl;
		}
		std::cout << std::endl;
	}
	else if (nb_val_list == 2)
	{
		if (list_to_sort[1] < list_to_sort[0])
			list_to_sort = this->_swaping(list_to_sort, 0, 1);
		std::cout << "final : " << list_to_sort[0] << ", " << list_to_sort[1] << std::endl;
		return (list_to_sort);
	}
	else if (nb_val_list == 1)
	{
	  std::cout << "final : " << list_to_sort[0]->max << std::endl;
		return (list_to_sort);
	}
	jacobsthal_list = this->_jacobstahl_compute(temp.size());
	for (std::vector<pm *>::iterator it = temp.begin(); it < temp.end(); it++)
	{
		res.push_back(*it);
	}
	for (size_t i = 0; i < jacobsthal_list.size(); i++)
	{
		std::cout << "in here" << std::endl;
		if (temp[jacobsthal_list[i] - 1]->lower.size() > 0)
		{
			pm	*elt_temp;
			elt_temp = temp[jacobsthal_list[i] - 1]->lower[temp[jacobsthal_list[i] - 1]->lower.size() - 1];
			std::cout << "elt : " << elt_temp->max << std::endl;
			res[jacobsthal_list[i] - 1]->lower.pop_back();
			
			res.insert(res.begin() + this->_binary_search(res, temp[jacobsthal_list[i] - 1]), elt_temp);
		}
	}
	if (rest)
	{
		for (std::vector<pm *>::iterator it = res.begin(); it < res.end(); it++)
		{
			if ((*it)->max > rest->max)
			{
				res.insert(it, rest);
				break ;
			}
		}
		// std::cout << "rest : " << rest->max << std::endl;
	}
	std::cout << "res : " << std::endl;
	for (size_t i = 0; i < res.size(); i++)
	{
		std::cout << res[i]->max << " " << res[i]->lower.size() << std::endl;
	}
	std::cout << std::endl;
	return (res);
}
