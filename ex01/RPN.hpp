#ifndef RPN_HPP

#define RPN_HPP

#include <iostream>
#include <deque>
#include <sstream>
#include <exception>

class RPN
{
	private:
		std::deque<std::string>	_value_list;
		std::deque<int>			_calculation_list;

		RPN();
		RPN(const RPN &cpy);
		RPN	&operator=(const RPN &obj);

	public:
		RPN(std::string list_input);
		~RPN();

		void	computing();
};

#endif