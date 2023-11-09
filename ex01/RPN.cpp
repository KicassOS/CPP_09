/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:30 by pszleper          #+#    #+#             */
/*   Updated: 2023/11/09 09:34:00 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN(void)
{
}

RPN::RPN(const RPN& other)
{
	*this = other;
}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
	{
		*this = other;
	}
	return *this;
}

RPN::~RPN(void)
{
}

void	RPN::calculate(std::string expression)
{
	int operand1 = 0, operand2 = 0;
	size_t	length = expression.length();

	for (size_t i = 0; i < length; i++)
	{
		if (!(expression[i] >= '0' && expression[i] <= '9') && !(expression[i] == '+' ||
			expression[i] == '-' || expression[i] == '*' || expression[i] == '/' || expression[i] == ' '))
			{
				std::cout << "Error: invalid symbol found" << std::endl;
				return ;
			}
	}
	for (size_t i = 0; i < length; i++)
	{
		if (expression[i] == ' ')
			continue;
		if (expression[i] >= '0' && expression[i] <= '9')
			this->_stack.push(expression[i] - 48);
		else
		{
			if (this->_stack.size() > 1)
				;
			else
			{
				std::cout << "Error: invalid notation !" << std::endl;
				while (this->_stack.empty() == 0)
				{
					this->_stack.pop();
				}
				return ;
			}
			if (expression[i] == '+')
			{
				operand2 = this->_stack.top();
				this->_stack.pop();
				operand1 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(operand1 + operand2);
			}
			else if (expression[i] == '-')
			{
				operand2 = this->_stack.top();
				this->_stack.pop();
				operand1 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(operand1 - operand2);
			}
			else if (expression[i] == '*')
			{
				operand2 = this->_stack.top();
				this->_stack.pop();
				operand1 = this->_stack.top();
				this->_stack.pop();
				this->_stack.push(operand1 * operand2);
			}
			else if (expression[i] == '/')
			{
				operand2 = this->_stack.top();
				this->_stack.pop();
				operand1 = this->_stack.top();
				this->_stack.pop();
				if (operand2 != 0)
					this->_stack.push(operand1 / operand2);
				else
				{
					std::cout << "Error: Division by zero is forbidden" << std::endl;
					while (this->_stack.empty() == 0)
					{
						this->_stack.pop();
					}
					return;
				}
			}
		}
	}
	if (this->_stack.size() != 1)
	{
		std::cout << "Error: stack.size() != 1" << std::endl;
		while (this->_stack.empty() == 0)
		{
			this->_stack.pop();
		}
		return ;
	}
	std::cout << this->_stack.top() << std::endl;
	while (this->_stack.empty() == 0)
		this->_stack.pop();
}
