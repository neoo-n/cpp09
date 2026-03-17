#ifndef	BITCOINEXCHANGE_HPP

#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>

class BitcoinExchange
{
	private:
		std::map<std::string, float>	_data_value;
		std::string						_file_data_name;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &cpy);
		BitcoinExchange	&operator=(const BitcoinExchange &obj);

		void	_setting_value();
		float	_find_value(std::string date);
		bool	_bad_input(std::string str);
		
	public:
		BitcoinExchange(std::string file_name);
		~BitcoinExchange();

		void	computing(std::string input_file);
};

#endif