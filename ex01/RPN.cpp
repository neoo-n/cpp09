#include "RPN.hpp"

// CONSTRUCTOR & DESTRUCTOR
RPN::RPN()
{

}

RPN::RPN(const RPN &cpy)
{
	if (this != &cpy)
	{
		this->_value_list = cpy._value_list;
	}
}

RPN::RPN(std::string list_input)
{
	std::stringstream	ss(list_input);
	std::string			temp;
	size_t				count;
	
	if (list_input.find_first_not_of("0123456789+-/* ") != std::string::npos)
	{
		throw std::invalid_argument("Error");
	}
	count = 0;
	while (count < list_input.size())
	{
		ss >> temp;
		if (!temp.empty())
			this->_value_list.push_back(temp);
		count += temp.size() + 1;
	}
}

RPN::~RPN()
{

}

RPN	&RPN::operator=(const RPN &obj)
{
	if (this != &obj)
	{
		this->_value_list = obj._value_list;
	}
	return (*this);
}

// METHODS
// PUBLIC
void	RPN::computing()
{
	int	temp;

	while (!this->_value_list.empty())
	{
		std::stringstream	ss;
		if (this->_value_list.front() == "+")
		{
			temp = this->_calculation_list.front();
			this->_calculation_list.pop_front();
			this->_calculation_list.front() += temp;
			this->_value_list.pop_front();
		}
		else if (this->_value_list.front() == "-")
		{
			temp = this->_calculation_list.front();
			this->_calculation_list.pop_front();
			this->_calculation_list.front() -= temp;
			this->_value_list.pop_front();
		}
		else if (this->_value_list.front() == "/")
		{
			temp = this->_calculation_list.front();
			this->_calculation_list.pop_front();
			this->_calculation_list.front() /= temp;
			this->_value_list.pop_front();
		}
		else if (this->_value_list.front() == "*")
		{
			temp = this->_calculation_list.front();
			this->_calculation_list.pop_front();
			this->_calculation_list.front() *= temp;
			this->_value_list.pop_front();
		}
		else
		{
			ss << this->_value_list.front();
			ss >> temp;
			this->_calculation_list.push_front(temp);
			this->_value_list.pop_front();
		}
	}
	std::cout << this->_calculation_list.front() << std::endl;
}