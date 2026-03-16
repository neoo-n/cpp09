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
		// std::cout << "temp : " << temp << ", nb : " << nb << std::endl;
	}
}

float	BitcoinExchange::find_value(std::string date)
{
	std::string		before_line;
	std::string		line;
	size_t			pos;
	time_t			closer_pos;
	std::ifstream	data_file;
	time_t			input;
	time_t			data;
	std::string		formatPattern = "%Y-%m-%d";  
    tm				timeParts = {};
	float			res;
    
	data_file.open("data.csv");
	if (!data_file.is_open())
	throw std::invalid_argument("File could not open.");
	
	strptime(date.c_str(), formatPattern.c_str(), &timeParts);
	input = mktime(&timeParts);
	getline(data_file, line);
	closer_pos = -1;
	while (getline(data_file, line))
	{
		pos = line.find(',');
		if (pos == std::string::npos)
		{
			continue ;
		}
		else
		{
			strptime((line.substr(0, pos)).c_str(), formatPattern.c_str(), &timeParts);
			data = std::mktime(&timeParts);
			if (std::abs(data - input) < closer_pos || closer_pos < 0)
				closer_pos = std::abs(data - input);
			else if (std::abs(data - input) > closer_pos)
				break ;
		}
		before_line = line;
	}
	std::cout << "line : " << before_line << std::endl;
	std::stringstream	ss(before_line.substr(pos + 1, before_line.size() - pos - 1));
	ss >> res;
	data_file.close();
	return (res);
}

bool	BitcoinExchange::bad_date(std::string date)
{
	std::string			year;
	std::string			month;
	std::string			day;
	std::stringstream	ss;
	int					val;
	std::string			formatPattern = "%Y-%m-%d";  
    tm					timeParts = {};
    
    if (!strptime(date.c_str(), formatPattern.c_str(), &timeParts))
    {
        return (true);
    }
	month = date.substr(5, 2);
	day = date.substr(8, 2);
	ss << year;
	ss >> val;
	if (month == "2" && ((val % 4 == 0 && day > "29") || (val % 4 != 0 && day > "28")))
		return (true);
	return (false);
}

// PUBLIC
void	BitcoinExchange::computing()
{
	for (std::multimap<std::string, float>::iterator it = this->_input_value.begin(); it != this->_input_value.end(); it++)
	{
		if (bad_date(it->first))
			std::cerr << "Error : bad input => " << it->first << std::endl;
		else
		{
			if (it->second < 0)
				std::cerr << "Error : not a positive number." << std::endl;
			else if (it->second > 1000)
				std::cerr << "Error : too large a number." << std::endl;
			else
				std::cout << it->first << " => " << it->second << " = " << it->second * this->find_value(it->first) << std::endl;
		}
	}
}