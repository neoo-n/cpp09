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

void	RPN::_parsing(std::string list_input)
{
	std::stringstream	ss1(list_input);
	std::string			temp;

	if (list_input.find_first_not_of("0123456789/*-+ ") != std::string::npos)
		throw std::invalid_argument("Error");
	while (ss1 >> temp)
	{
		if (temp.size() > 1 && (temp.find_first_of("+-*/") != std::string::npos))
		{
			throw std::invalid_argument("Error");
		}
	}
}

// METHODS
// PUBLIC
void	RPN::computing(std::string list_input)
{
	std::stringstream	ss1(list_input);
	std::string			temp;
	int					value;

	this->_parsing(list_input);
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
			if (value > 9 || value < 0)
				throw std::invalid_argument("Error");
			this->_value_stack.push(value);
		}
	}
	if (this->_value_stack.size() != 1)
		throw std::invalid_argument("Error");
	std::cout << this->_value_stack.top() << std::endl;
}