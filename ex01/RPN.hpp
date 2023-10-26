/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:32 by pszleper          #+#    #+#             */
/*   Updated: 2023/10/26 05:59:38 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <stack>

class RPN
{
	public:
		RPN(void);
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);
		~RPN(void);

		void	calculate(std::string expression);
	
	private:
		std::stack<int> _stack;
};

#endif
