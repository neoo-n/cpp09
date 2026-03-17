#include "BitcoinExchange.hpp"

// CONSTRUCTOR & DESTRUCTOR
BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &cpy)
{
	if (this != &cpy)
	{
		this->_data_value = cpy._data_value;
			throw std::invalid_argument("File could not open.");
	}
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &obj)
{
	if (this != &obj)
	{
		this->_data_value = obj._data_value;
		this->_file_data_name = obj._file_data_name;
	}
	return (*this);
}

BitcoinExchange::BitcoinExchange(std::string file_name)
: _file_data_name(file_name)
{
	this->_setting_value();
}

// METHODS

// PRIVATE

void	BitcoinExchange::_setting_value()
{
	std::string		line;
	size_t			pos;
	std::string		temp;
	float			nb;
	std::ifstream	data_file;

	data_file.open(this->_file_data_name.c_str());
	if (!data_file.is_open())
		throw std::invalid_argument("Error : could not open file.");

	getline(data_file, line);
	while (getline(data_file, line))
	{
		pos = line.find(',');
		if (pos == std::string::npos)
		{
			continue ;
		}
		else
		{
			line[pos] = ' ';

			std::stringstream	ss(line);
			ss >> temp;
			ss >> nb;
		}
		this->_data_value.insert(std::make_pair(temp, nb));
	}
}

float	BitcoinExchange::_find_value(std::string date)
{
	std::map<std::string, float>::iterator	pos;

	pos = this->_data_value.upper_bound(date);
	pos--;
	return (pos->second);
}

bool	BitcoinExchange::_bad_input(std::string str)
{
	int					year;
	int					month;
	int					day;
	float				res;
	
	if (std::sscanf(str.c_str(), "%d-%d-%d | %f", &year, &month, &day, &res) < 4)
		return (true);
	if (month <= 0 || day <= 0)
		return (true);
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (day > 31)
				return (true);
			break ;

		case 2:
			if ((year % 4 == 0 && day > 29) || ((year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) && day > 28))
				return (true);
			break ;

		case 4:
		case 6:
		case 9:
		case 11:
			if (day > 30)
				return (true);
			break ;
		default :
			return (true);
	}
	return (false);
}

// PUBLIC
void	BitcoinExchange::computing(std::string input_file)
{
	std::ifstream		file;
	std::string			line;
	std::string			temp;
	float				nb;
	size_t				pos;
	int					count;

	file.open(input_file.c_str());
	if (!file.is_open())
		throw std::invalid_argument("Error : could not open input file.");
	count = 0;
	while (getline(file, line))
	{
		if (line == "date | value")
		{
			if (count == 0)
			{
				count++;
				continue ;
			}
			else
			{
				std::cerr << "Error : bad input => " << line << std::endl;
				continue ;
			}
		}
		pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << "Error : bad input => " << line << std::endl;
			continue ;
		}
		if (this->_bad_input(line))
			std::cerr << "Error : bad input => " << line << std::endl;
		else
		{
			line[pos] = ' ';
			std::stringstream	ss(line);
			ss >> temp;
			ss >> nb;
			if (nb < 0)
				std::cerr << "Error : not a positive number." << std::endl;
			else if (nb > 1000)
				std::cerr << "Error : too large a number." << std::endl;
			else
				std::cout << temp << " => " << nb << " = " << nb * this->_find_value(temp) << std::endl;
		}
	}
}