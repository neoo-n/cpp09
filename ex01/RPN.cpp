#include "RPN.hpp"

// CONSTRUCTOR & DESTRUCTOR
RPN::RPN()
{

}

RPN::RPN(const RPN &cpy)
{
	if (this != &cpy)
	{
		this->_value_stack = cpy._value_stack;
	}
}

RPN::~RPN()
{

}

RPN	&RPN::operator=(const RPN &obj)
{
	if (this != &obj)
	{
		this->_value_stack = obj._value_stack;
	}
	return (*this);
}

// METHODS
// PUBLIC
void	RPN::computing(std::string list_input)
{
	std::stringstream	ss1(list_input);
	std::string			temp;
	int					value;

	if (list_input.find_first_not_of("0123456789/*-+ ") != std::string::npos)
		throw std::invalid_argument("Error");
	while (ss1 >> temp)
	{
		std::stringstream	ss;
		if (temp == "+")
		{
			value = this->_value_stack.top();
			this->_value_stack.pop();
			this->_value_stack.top() += value;
		}
		else if (temp == "-")
		{
			value = this->_value_stack.top();
			this->_value_stack.pop();
			this->_value_stack.top() -= value;
		}
		else if (temp == "/")
		{
			value = this->_value_stack.top();
			this->_value_stack.pop();
			this->_value_stack.top() /= value;
		}
		else if (temp == "*")
		{
			value = this->_value_stack.top();
			this->_value_stack.pop();
			this->_value_stack.top() *= value;
		}
		else
		{
			ss << temp;
			ss >> value;
			this->_value_stack.push(value);
		}
	}
	std::cout << this->_value_stack.top() << std::endl;
}