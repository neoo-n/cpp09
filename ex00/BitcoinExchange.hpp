#ifndef	BITCOINEXCHANGE_HPP

#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <ctime>
#include <cmath>
#include <list>
#include <fstream>
#include <sstream>
#include <exception>

class BitcoinExchange
{
	private:
		std::list<std::pair<std::string, float> >	_input_value;
		std::string									_file_input_name;
		std::ifstream								_file_input;

		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &cpy);
		BitcoinExchange	&operator=(const BitcoinExchange &obj);

		void	setting_value();
		float	find_value(std::string date);
		bool	bad_date(std::string date);
		
	public:
		BitcoinExchange(std::string file_name);
		~BitcoinExchange();

		void	computing();
};

#endif