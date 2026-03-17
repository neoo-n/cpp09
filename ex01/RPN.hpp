#ifndef RPN_HPP

#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <exception>

class RPN
{
	private:
		std::stack<int>		_value_stack;

		RPN(const RPN &cpy);
		RPN	&operator=(const RPN &obj);
		
		public:
		RPN();
		~RPN();

		void	computing(std::string list_input);
};

#endif