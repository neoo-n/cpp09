#ifndef PMERGEME_HPP

#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <exception>

class PmergeMe
{
	private:
		std::vector<int>	_values;

		PmergeMe();
		PmergeMe(const PmergeMe &cpy);

		bool	_isDuplicate(int temp);
		void	_parsing(int ac, char **av);
	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe	&operator=(const PmergeMe &obj);

		void	sorting_vect(std::vector<int> list_to_sort);
};

#endif