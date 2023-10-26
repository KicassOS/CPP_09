/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:27 by pszleper          #+#    #+#             */
/*   Updated: 2023/10/26 05:59:38 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: invalid number of arguments" << std::endl;
		return (1);
	}

	RPN calculator;
	calculator.calculate(argv[1]);
	return (0);
}
