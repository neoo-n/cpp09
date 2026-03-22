#ifndef PMERGEME_HPP

#define PMERGEME_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>
#include <exception>

struct pm_vect
{
	int					max;
	std::vector<pm_vect *>	lower;
};

struct pm_deque
{
	int						max;
	std::deque<pm_deque *>	lower;
};

class PmergeMe
{
	private:
		std::vector<pm_vect *>	_elt_vect;
		std::deque<pm_deque *>	_elt_deque;

		PmergeMe();
		PmergeMe(const PmergeMe &cpy);

		bool	_isDuplicate(int temp);
		void	_parsing(int ac, char **av);

		std::vector<int>	_jacobstahl_compute(int size);
		int					_binary_search_vect(std::vector<pm_vect *> v, pm_vect *elt_max, pm_vect *elt_min);
		int					_binary_search_deque(std::deque<pm_deque *> d, pm_deque *elt_max, pm_deque *elt_min);
		int					_find_index_vect(std::vector<pm_vect *> v, pm_vect *elt);
		int					_find_index_deque(std::deque<pm_deque *> d, pm_deque *elt);

		void	_print_vect(std::vector<pm_vect *> v);
		void	_print_deque(std::deque<pm_deque *> d);

	public:
		PmergeMe(int ac, char **av);
		~PmergeMe();
		PmergeMe	&operator=(const PmergeMe &obj);

		std::vector<pm_vect *>	sorting_vect(std::vector<pm_vect *> list_to_sort);
		std::deque<pm_deque *>	sorting_deque(std::deque<pm_deque *> list_to_sort);
		void				sorting();
		void				is_sorted(std::vector<pm_vect *> v, std::deque<pm_deque *> d);
};

#endif
