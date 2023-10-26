/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:25 by pszleper          #+#    #+#             */
/*   Updated: 2023/10/26 05:12:15 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char** argv)
{
	std::ifstream	dataFile, inputFile;
	
	if (argc != 2)
    {
        std::cout << "Error: Invalid number of arguments" << std::endl;
		return (1);
    }
	dataFile.open("data.csv");
	if (!dataFile.is_open())
    {
        std::cout << "Error: Could not open the data.csv file, make sure it exists" << std::endl;
        return (1);
    }
    inputFile.open(argv[1]);
	if (!inputFile.is_open())
    {
        std::cout << "Error: could not open the file passed as argument, make sure it exists" << std::endl;
        return (1);
    }
	BitcoinExchange btc(dataFile);
	btc.displayResult(inputFile);
	dataFile.close();
	inputFile.close();
	return (0);
}
