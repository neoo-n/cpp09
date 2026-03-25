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
		throw std::invalid_argument("Error : invalid argument");
	while (ss1 >> temp)
	{
		if (temp.size() > 1 && (temp.find_first_of("+-*/") != std::string::npos))
		{
			throw std::invalid_argument("Error : invalid argument");
		}
	}
}

// METHODS
// PUBLIC
void	RPN::computing(std::string list_input)
{
	std::stringstream	ss1(list_input);
	std::string			temp;
	double				value1;
	double				value2;
	double				res;

	this->_parsing(list_input);
	while (ss1 >> temp)
	{
		std::stringstream	ss;
		if (temp == "+")
		{
			if (this->_value_stack.size() < 2)
				throw std::length_error("Error : not enough number for operation");
			value1 = this->_value_stack.top();
			this->_value_stack.pop();
			value2 = this->_value_stack.top();
			this->_value_stack.pop();
			res = value2 + value1;
			if (res > 2147483647)
				throw std::overflow_error("Error : overflow");
			this->_value_stack.push(res);
		}
		else if (temp == "-")
		{
			if (this->_value_stack.size() < 2)
				throw std::length_error("Error : not enough number for operation");
			value1 = this->_value_stack.top();
			this->_value_stack.pop();
			value2 = this->_value_stack.top();
			this->_value_stack.pop();
			res = value2 - value1;
			if (res > 2147483647)
				throw std::overflow_error("Error : overflow");
			this->_value_stack.push(res);
		}
		else if (temp == "/")
		{
			if (this->_value_stack.size() < 2)
				throw std::length_error("Error : not enough number for operation");
			value1 = this->_value_stack.top();
			this->_value_stack.pop();
			value2 = this->_value_stack.top();
			this->_value_stack.pop();
			if (value1 == 0.0)
				throw std::logic_error("Error");
			res = value2 / value1;
			if (res > 2147483647)
				throw std::overflow_error("Error : overflow");
			this->_value_stack.push(res);
		}
		else if (temp == "*")
		{
			if (this->_value_stack.size() < 2)
				throw std::length_error("Error : not enough number for operation");
			value1 = this->_value_stack.top();
			this->_value_stack.pop();
			value2 = this->_value_stack.top();
			this->_value_stack.pop();
			res = value2 * value1;
			if (res > 2147483647)
				throw std::overflow_error("Error : overflow");
			this->_value_stack.push(res);
		}
		else
		{
			ss << temp;
			ss >> value1;
			if (value1 > 9 || value1 < 0)
				throw std::invalid_argument("Error : number not between 0 and 9");
			this->_value_stack.push(value1);
		}
	}
	if (this->_value_stack.size() != 1)
		throw std::invalid_argument("Error : not enough operation");
	std::cout << this->_value_stack.top() << std::endl;
}