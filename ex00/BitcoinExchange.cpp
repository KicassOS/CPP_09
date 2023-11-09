/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:20 by pszleper          #+#    #+#             */
/*   Updated: 2023/11/09 09:45:00 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(std::ifstream& dataFile)
{
	size_t							datePart = 0, comma = 0;
	std::pair<std::string, float>	rateAndText;
	std::string						eachLine = "", date = "", rate = "";

	std::getline(dataFile, eachLine); // skip first line
	while (std::getline(dataFile, eachLine))
	{
		comma   = eachLine.find(',');
		date    = eachLine.substr(0, comma);
		if (comma != std::string::npos)
			rate = eachLine.substr(comma + 1);
		datePart = checkDate(date);
		if (!datePart)
		{
			_data.clear();
			std::cout << "Error: bad input => " << date << std::endl;
			return ;
		}
		rateAndText = checkValue(rate);
		if (rateAndText.first != "valid")
		{
			_data.clear();
			std::cout << "[data.csv] " << rateAndText.first;
			return ;
		}
		_data[datePart] = rateAndText.second;
	}
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	for (std::map<unsigned int, float>::const_iterator it = other._data.begin(); it != other._data.end(); ++it)
		this->_data[it->first] = it->second;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
	{
		this->_data.clear();
		for (std::map<unsigned int, float>::const_iterator it = other._data.begin(); it != other._data.end(); ++it)
			this->_data[it->first] = it->second;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange(void)
{
}

void	BitcoinExchange::trimStr(std::string& lineStr)
{
	size_t  begin = lineStr.find_first_not_of(" \f\n\r\t\v");
	lineStr.erase(0, begin);
	size_t  end = lineStr.find_last_not_of(" \f\n\r\t\v");
	lineStr.erase(end + 1);
}

unsigned int	BitcoinExchange::calculateDays(int year, int month, int day)
{
	// During leap years, which occur every 4 years, we add an extra day, Leap Day, on 29 February
	// 1582 is the year the Gregorian calendar was adopted
	// The Gregorian calendar differs from the Julian only in that no century year (1800, 1900 etc..) is a leap year unless it is exactly divisible by 400
	int february = 28 + (((year < 1582) && (year % 4 == 0)) || ((year >= 1582) && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)));
	int months[12] = {31, february, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int accumulate = std::accumulate(months, months + (month - 1), 0);
	int daysTillDate = accumulate + day;

	unsigned int	leapYears = 0;
	for (int i = 1; i < year; ++i)
		leapYears += (((year < 1582) && (i % 4 == 0)) || ((year >= 1582) && ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)));
	unsigned int	daysCalculated = leapYears + 365 * (year - 1) + daysTillDate; 
		return (daysCalculated);
}

unsigned int	BitcoinExchange::checkDate(const std::string& dateStr)
{
	size_t  forbiddenChars = dateStr.find_first_not_of("-0123456789");
	if (dateStr.length() != 10 || forbiddenChars != std::string::npos || dateStr[4] != '-' || dateStr[7] != '-')
	return (0);

	std::string			yyyy = dateStr.substr(0, 4);
	std::istringstream	yearStream(yyyy);
	std::string			mm = dateStr.substr(5, 2);
	std::istringstream	monthStream(mm);
	std::string			dd = dateStr.substr(8, 2);
	std::istringstream	dayStream(dd);

	int year, month, day;
	yearStream>>year;
	monthStream>>month;
	dayStream>>day;

	if (year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return (0);

	int daysInMonth = 31;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		daysInMonth = 30;
	else if (month == 2)
		daysInMonth = 28 + (((year < 1582) && (year % 4 == 0)) || ((year >= 1582) && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)));
	if (day > daysInMonth)
		return (0);
	return calculateDays(year, month, day);
}

std::pair<std::string, float>	BitcoinExchange::checkValue(const std::string& valueStr)
{
	if (valueStr == "" || valueStr == "+" || valueStr == "-")
		return std::make_pair("Error: missing value", 0.0);
	size_t  forbiddenChars = valueStr.find_first_not_of("0123456789");
	if (valueStr[0] == '-' || valueStr[0] == '+')
		forbiddenChars = valueStr.substr(1).find_first_not_of("0123456789");
	if (forbiddenChars == std::string::npos)
	{
		std::stringstream  valueStream(valueStr);
		long long integerValue;
		valueStream >> integerValue;
		if (integerValue > INT_MAX)
			return std::make_pair("Error: too large a number.\n", 0.0);
		if (integerValue < INT_MIN)
			return std::make_pair("Error: number too small.\n", 0.0);
		if (integerValue < 0)
			return std::make_pair("Error: not a positive number.\n", 0.0);
		return std::make_pair("valid", static_cast<float>(integerValue));
	}
	char*	end;
	float	floatValue = strtof(valueStr.c_str(), &end);
	if (*end != '\0')
		return std::make_pair("Error: invalid number.\n", 0.0);
	if (floatValue == HUGE_VALF)
		return std::make_pair("Error: too large a number.\n", 0.0);
	if (floatValue < -HUGE_VALF)
		return std::make_pair("Error: number too small.\n", 0.0);
	if (floatValue < 0)
		return std::make_pair("Error: not a positive number.\n", 0.0);
	return std::make_pair("valid", floatValue);
}

void	BitcoinExchange::displayResult(std::ifstream& inputFile)
{
	if (_data.empty())
		return ;
	size_t									datePart, pipe_char_index;
	std::string								eachLine, date, value;
	std::pair<std::string, float>			valueAndText;
	std::map<unsigned int, float>::iterator	it, startIt;

	startIt = _data.begin();
	std::getline(inputFile, eachLine); // skip first line
	while(std::getline(inputFile, eachLine))
	{
		pipe_char_index = eachLine.find('|');
		date = eachLine.substr(0, pipe_char_index);
		value = "";
		if (pipe_char_index != std::string::npos)
			value = eachLine.substr(pipe_char_index + 1);
		this->trimStr(date);
		this->trimStr(value);
		datePart = checkDate(date);
		if (datePart)
		{
			it = _data.find(datePart);
			while (--datePart && datePart >= startIt->first && it == _data.end())
				it = _data.find(datePart);
			if (it == _data.end())
				std::cout << "Error: the following date was not found in data.csv => " << date << std::endl;
			else
			{
				valueAndText = checkValue(value);
				if (valueAndText.first != "valid")
				{
					std::cout << valueAndText.first;
					if (value == "")
						std::cout << date << std::endl;
				}
				else if (valueAndText.second > 1000)
					std::cout << "Error: price is greater than 1000: " << value << std::endl;
				else
				{
					std::cout << date << " => " << valueAndText.second << " = " << valueAndText.second * (it->second) << std::endl;
				}
			}
		}
		else
			std::cout << "Error: bad input => " << date << std::endl;
	}
}
