#ifndef PMERGEME_HPP

#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
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

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe	&operator=(const PmergeMe &obj);

		std::vector<pm *>	getElt() const;

		std::vector<pm *>	sorting_vect(std::vector<pm *> list_to_sort);
};

#endif
