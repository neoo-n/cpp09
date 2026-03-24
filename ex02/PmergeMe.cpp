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
		for (size_t i = 0; i < cpy._elt_vect.size(); i++)
		{
			pm_vect *elt = new pm_vect;
			elt->max = cpy._elt_vect[i]->max;
			elt->lower = cpy._elt_vect[i]->lower;
			this->_elt_vect.push_back(elt);
		}
		for (size_t i = 0; i < cpy._elt_deque.size(); i++)
		{
			pm_deque *elt = new pm_deque;
			elt->max = cpy._elt_deque[i]->max;
			elt->lower = cpy._elt_deque[i]->lower;
			this->_elt_deque.push_back(elt);
		}
	}
}

PmergeMe::~PmergeMe()
{
}

void	PmergeMe::_cleaning()
{
	size_t	size;

	size = this->_elt_vect.size();
	for (size_t i = 0; i < size; i++)
	{
		if (this->_elt_vect[i])
			delete this->_elt_vect[i];
	}
	size = this->_elt_deque.size();
	for (size_t i = 0; i < size; i++)
	{
		if (this->_elt_deque[i])
			delete this->_elt_deque[i];
	}
}
PmergeMe	&PmergeMe::operator=(const PmergeMe &obj)
{
	if (this != &obj)
	{
		for (size_t i = 0; i < obj._elt_vect.size(); i++)
		{
			pm_vect *elt = new pm_vect;
			elt->max = obj._elt_vect[i]->max;
			elt->lower = obj._elt_vect[i]->lower;
			this->_elt_vect.push_back(elt);
		}
		for (size_t i = 0; i < obj._elt_deque.size(); i++)
		{
			pm_deque *elt = new pm_deque;
			elt->max = obj._elt_deque[i]->max;
			elt->lower = obj._elt_deque[i]->lower;
			this->_elt_deque.push_back(elt);
		}
	}
	return (*this);
}

//METHODS
//PRIVATE

bool	PmergeMe::_isDuplicate(int temp)
{
	for (size_t	i = 0; i < this->_elt_vect.size(); i++)
	{
		if (this->_elt_vect[i]->max == temp)
			return (true);
	}
	for (size_t	i = 0; i < this->_elt_deque.size(); i++)
	{
		if (this->_elt_deque[i]->max == temp)
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
		if (str_temp.size() == 0)
		{
			this->_cleaning();
			throw std::invalid_argument("Error : not a value");
		}
		if (str_temp.find_first_not_of("1234567890") != std::string::npos)
		{
			this->_cleaning();
			throw std::invalid_argument("Error : invalid input");
		}
		std::stringstream	ss(str_temp);
		ss >> temp;
		if (temp == 0)
		{
			this->_cleaning();
			throw std::invalid_argument("Error : input has value zero");
		}
		if (this->_isDuplicate(temp))
		{
			this->_cleaning();
			throw std::invalid_argument("Error : invalid input, it's a duplicate");
		}
		pm_vect	*elt_vect = new pm_vect;
		elt_vect->max = temp;
		this->_elt_vect.push_back(elt_vect);
		pm_deque	*elt_deque = new pm_deque;
		elt_deque->max = temp;
		this->_elt_deque.push_back(elt_deque);
	}
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
	while (val < size)
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
		second_prev = prev;
		prev = val;
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

int	PmergeMe::_binary_search_vect(std::vector<pm_vect *> v, pm_vect *elt_max, pm_vect *elt_min)
{
	size_t						index_max;
	size_t						index_min;
	size_t						index_look;

	index_max = this->_find_index_vect(v, elt_max);
	if (index_max == 0)
		return (0);
	index_min = 0;
	index_look = (index_max - index_min) / 2;
	while (index_min < index_max - 1)
	{
		if (v[index_look]->max < elt_min->max)
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
	if (elt_min->max < v[index_min]->max)
		return (index_min);
	return (index_max);
}

int	PmergeMe::_binary_search_deque(std::deque<pm_deque *> d, pm_deque *elt_max, pm_deque *elt_min)
{
	size_t						index_max;
	size_t						index_min;
	size_t						index_look;

	index_max = this->_find_index_deque(d, elt_max);
	if (index_max == 0)
		return (0);
	index_min = 0;
	index_look = (index_max - index_min) / 2;
	while (index_min < index_max - 1)
	{
		if (d[index_look]->max < elt_min->max)
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
	if (elt_min->max < d[index_min]->max)
		return (index_min);
	return (index_max);
}

int	PmergeMe::_find_index_vect(std::vector<pm_vect *> v, pm_vect *elt)
{
	int	index;

	index = std::find(v.begin(), v.end(), elt) - v.begin();
	return (index); 
}

int	PmergeMe::_find_index_deque(std::deque<pm_deque *> d, pm_deque *elt)
{
	int	index;

	index = std::find(d.begin(), d.end(), elt) - d.begin();
	return (index); 
}

void	PmergeMe::_print_vect(std::vector<pm_vect *> v)
{
	size_t	size_vect;

	size_vect = v.size();
	for (size_t i = 0; i < size_vect && i < 10; i++)
	{
		std::cout << v[i]->max;
		if (i < size_vect - 1)
			std::cout << " ";
	}
	if (size_vect > 10)
		std::cout << "[...]";
}

void	PmergeMe::_print_deque(std::deque<pm_deque *> d)
{
	size_t	size_deque;

	size_deque = d.size();
	for (size_t i = 0; i < size_deque && i < 10; i++)
	{
		std::cout << d[i]->max;
		if (i < size_deque - 1)
			std::cout << " ";
	}
	if (size_deque > 10)
		std::cout << "[...]";
}

// PUBLIC

std::vector<pm_vect *>	PmergeMe::sorting_vect(std::vector<pm_vect *> list_to_sort)
{
	size_t				nb_val_list;
	size_t				half_nb;
	std::vector<pm_vect *>	val;
	std::vector<pm_vect *>	res;
	std::vector<pm_vect *>	temp;
	std::vector<int>	jacobsthal_list;
	pm_vect					*rest;

	rest = NULL;
	nb_val_list = list_to_sort.size();
	if (nb_val_list > 2)
	{
		half_nb = list_to_sort.size() / 2;
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
			rest = list_to_sort[nb_val_list - 1];
		}
		temp = this->sorting_vect(val);
	}
	else if (nb_val_list == 2)
	{
		if (list_to_sort[1]->max < list_to_sort[0]->max)
		{
			list_to_sort.insert(list_to_sort.begin(), list_to_sort[1]);
			list_to_sort.pop_back();
		}
		return (list_to_sort);
	}
	else if (nb_val_list == 1)
		return (list_to_sort);
	jacobsthal_list = this->_jacobstahl_compute(temp.size());
	for (std::vector<pm_vect *>::iterator it = temp.begin(); it < temp.end(); it++)
	{
		res.push_back(*it);
	}
	for (size_t i = 0; i < jacobsthal_list.size(); i++)
	{
		if (temp[jacobsthal_list[i] - 1]->lower.size() > 0)
		{
			pm_vect	*elt_temp;
			elt_temp = temp[jacobsthal_list[i] - 1]->lower[temp[jacobsthal_list[i] - 1]->lower.size() - 1];
			res[this->_find_index_vect(res, temp[jacobsthal_list[i] - 1])]->lower.pop_back();
			int index = this->_binary_search_vect(res, temp[jacobsthal_list[i] - 1] , elt_temp);
			res.insert(res.begin() + index, elt_temp);
		}
	}
	if (rest)
	{
		for (std::vector<pm_vect *>::iterator it = res.begin(); it < res.end(); it++)
		{
			if ((*it)->max > rest->max)
			{
				res.insert(it, rest);
				break ;
			}
			else
			{
				if (it == res.end() - 1)
				{
					res.push_back(rest);
					break ;
				}
			}
		}
	}
	return (res);
}

std::deque<pm_deque *>	PmergeMe::sorting_deque(std::deque<pm_deque *> list_to_sort)
{
	size_t					nb_val_list;
	size_t					half_nb;
	std::deque<pm_deque *>	val;
	std::deque<pm_deque *>	res;
	std::deque<pm_deque *>	temp;
	std::vector<int>		jacobsthal_list;
	pm_deque				*rest;

	rest = NULL;
	nb_val_list = list_to_sort.size();
	if (nb_val_list > 2)
	{
		half_nb = list_to_sort.size() / 2;
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
			rest = list_to_sort[nb_val_list - 1];
		}
		temp = this->sorting_deque(val);
	}
	else if (nb_val_list == 2)
	{
		if (list_to_sort[1]->max < list_to_sort[0]->max)
		{
			list_to_sort.insert(list_to_sort.begin(), list_to_sort[1]);
			list_to_sort.pop_back();
		}
		return (list_to_sort);
	}
	else if (nb_val_list == 1)
		return (list_to_sort);
	jacobsthal_list = this->_jacobstahl_compute(temp.size());
	for (std::deque<pm_deque *>::iterator it = temp.begin(); it < temp.end(); it++)
	{
		res.push_back(*it);
	}
	for (size_t i = 0; i < jacobsthal_list.size(); i++)
	{
		if (temp[jacobsthal_list[i] - 1]->lower.size() > 0)
		{
			pm_deque	*elt_temp;
			elt_temp = temp[jacobsthal_list[i] - 1]->lower[temp[jacobsthal_list[i] - 1]->lower.size() - 1];
			res[this->_find_index_deque(res, temp[jacobsthal_list[i] - 1])]->lower.pop_back();
			int index = this->_binary_search_deque(res, temp[jacobsthal_list[i] - 1] , elt_temp);
			res.insert(res.begin() + index, elt_temp);
		}
	}
	if (rest)
	{
		for (std::deque<pm_deque *>::iterator it = res.begin(); it < res.end(); it++)
		{
			if ((*it)->max > rest->max)
			{
				res.insert(it, rest);
				break ;
			}
			else
			{
				if (it == res.end() - 1)
				{
					res.push_back(rest);
					break ;
				}
			}
		}
	}
	return (res);
}

void	PmergeMe::sorting()
{
	std::vector<pm_vect *>	vect_res;
	clock_t					time_vect;
	clock_t					time_end_vect;
	std::deque<pm_deque *>	deque_res;
	clock_t					time_deque;
	clock_t					time_end_deque;

	time_vect = std::clock();
	vect_res = this->sorting_vect(this->_elt_vect);
	time_end_vect = std::clock();
	time_deque = std::clock();
	deque_res = this->sorting_deque(this->_elt_deque);
	time_end_deque = std::clock();
	std::cout << "Before : ";
	this->_print_vect(this->_elt_vect);
	std::cout << std::endl; 
	std::cout << "After : ";
	this->_print_vect(vect_res);
	std::cout << std::endl; 
	std::cout << "Time to process a range of " << this->_elt_vect.size() << " elements with std::vector : " << 1000.0 * (time_end_vect - time_vect) / CLOCKS_PER_SEC << " ms" << std::endl;
	std::cout << "Time to process a range of " << this->_elt_deque.size() << " elements with std::deque : " << 1000.0 * (time_end_deque - time_deque) / CLOCKS_PER_SEC << " ms" << std::endl;

	// this->is_sorted(vect_res, deque_res);
	for (size_t	i = 0; i < vect_res.size() ; i++)
	{
		delete vect_res[i];
	}
	for (size_t	i = 0; i < deque_res.size() ; i++)
	{
		delete deque_res[i];
	}
}

void	PmergeMe::is_sorted(std::vector<pm_vect *> v, std::deque<pm_deque *> d)
{
	size_t	size_vect;
	size_t	size_deque;
	bool	is_sorted;
	size_t	index;

	size_vect = v.size();
	size_deque = d.size();
	is_sorted = true;
	index = 0;
	for (; index < size_vect - 1; index++)
	{
		if (v[index]->max > v[index + 1]->max)
		{
			is_sorted = false;
			break ;
		}
	}
	if (is_sorted)
		std::cout << "it is sorted" << std::endl;
	else
		std::cout << "it is not sorted : " << v[index]->max << ", " << v[index + 1]->max << ", index : "<< index << std ::endl;
	index = 0;
	for (; index < size_deque - 1; index++)
	{
		if (d[index]->max > d[index + 1]->max)
		{
			is_sorted = false;
			break ;
		}
	}
	if (is_sorted)
		std::cout << "it is sorted" << std::endl;
	else
		std::cout << "it is not sorted : " << d[index]->max << ", " << d[index + 1]->max << ", index : "<< index << std ::endl;
}