#ifndef PMERGEME_HPP

#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <ctime>
#include <exception>

struct pm
{
	int					max;
	std::vector<pm *>	lower;
};

class PmergeMe
{
	private:
		std::vector<pm *>	_elt;

		PmergeMe();
		PmergeMe(const PmergeMe &cpy);

		bool	_isDuplicate(int temp);
		void	_parsing(int ac, char **av);

		std::vector<pm *>	_swaping(std::vector<pm *> v, size_t i1, size_t i2);
		std::vector<int>	_jacobstahl_compute(int size);
		int					_binary_search(std::vector<pm *> v, pm *elt_max, pm *elt_min);
		int					_find_index(std::vector<pm *> v, pm *elt);

		void	_print_vect(std::vector<pm *> v);

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe	&operator=(const PmergeMe &obj);

		std::vector<pm *>	getElt() const;

		std::vector<pm *>	sorting_vect(std::vector<pm *> list_to_sort);
		void				sorting(std::vector<pm *> list_to_sort);
};

#endif
