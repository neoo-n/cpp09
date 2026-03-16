#include "BitcoinExchange.hpp"

// CONSTRUCTOR & DESTRUCTOR
BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	if (this != &cpy)
	{
		this->_input_value = cpy._input_value;
		this->_file_input_name = cpy._file_input_name;
		if (this->_file_input.is_open())
			this->_file_input.close();
		this->_file_input.open(this->_file_input_name.c_str());
		if (!this->_file_input.is_open())
			throw std::invalid_argument("File could not open.");
	}
}

BitcoinExchange::~BitcoinExchange()
{
	if (this->_file_input.is_open())
	this->_file_input.close();
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this != &obj)
	{
		this->_input_value = obj._input_value;
		this->_file_input_name = obj._file_input_name;
		if (this->_file_input.is_open())
		this->_file_input.close();
		this->_file_input.open(this->_file_input_name.c_str());
		if (!this->_file_input.is_open())
			throw std::invalid_argument("File could not open.");
	}
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::string file_name)
: _file_input_name(file_name)
{
	this->_file_input.open(this->_file_input_name.c_str());
	if (!this->_file_input.is_open())
		throw std::invalid_argument("File could not open.");
	setting_value();
}

// METHODS

// PRIVATE
void	BitcoinExchange::setting_value()
{
	std::string			line;
	size_t				pos;
	std::string			temp;
	float				nb;

	while (getline(this->_file_input, line))
	{
		pos = line.find('|');
		if (pos == std::string::npos)
		{
			pos = line.size();
			temp = line;
			nb = 0;
		}
		else
		{
			line[pos] = ' ';
			std::stringstream	ss(line);
			ss >> temp;
			ss >> nb;
		}
		this->_input_value.insert(std::make_pair(temp, nb));
		std::cout << "temp : " << temp << ", nb : " << nb << std::endl;
	}
}

// PUBLIC
void	BitcoinExchange::computing()
{
	std::ifstream	data_file;

	data_file.open("data.csv");
	if (!data_file.is_open())
		throw std::invalid_argument("File could not open.");

}