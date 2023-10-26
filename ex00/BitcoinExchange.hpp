/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:23 by pszleper          #+#    #+#             */
/*   Updated: 2023/10/26 05:18:08 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <string>
# include <numeric>
# include <climits>
# include <algorithm>
# include <map>
# include <fstream>
# include <sstream>
# include <cmath>

class BitcoinExchange
{
	public:
		BitcoinExchange(void);
		BitcoinExchange(std::ifstream& dataFile);
		BitcoinExchange(const BitcoinExchange& other);
		~BitcoinExchange(void);
		BitcoinExchange&	operator=(const BitcoinExchange& other);
		void				displayResult(std::ifstream& inputFile);
	
	private:
		void							trimStr(std::string& lineStr);
		unsigned int					calculateDays(int year, int month, int day);
		unsigned int					checkDate(const std::string& dateStr);
		std::pair<std::string, float>	checkValue(const std::string& valueStr);

		std::map<unsigned int, float>	_data;
};

#endif
