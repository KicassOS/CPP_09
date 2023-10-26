/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pszleper <pszleper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:36:40 by pszleper          #+#    #+#             */
/*   Updated: 2023/10/26 06:27:38 by pszleper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <algorithm>
# include <vector>
# include <list>
# include <sstream>
# include <climits>
# include <exception>
# include <sys/time.h>

class PmergeMe
{
	public:
		PmergeMe(void); 
		PmergeMe(const std::string& numSequence);
		PmergeMe(const PmergeMe& other);
		PmergeMe&	operator=(const PmergeMe& other);
		~PmergeMe(void);

		int		getVectorSize(void) const;
		int		getListSize(void) const;

		void	vectorFordJohnson(int begin, int end);
		void	listFordJohnson(int begin, int end);

		void	checkVectorSort(void);
		void	checkListSort(void);

		void	displayVector(unsigned int value) const;
		void	displayList(unsigned int value) const;

	private:
		std::vector<int>	_vector;
		std::list<int>		_list;
		int					_vectorAction;
		int					_listAction;

		void				fillContainer(std::string& numSequence);
		void				vectorInsertionSort(int begin, int end);
		void				vectorMergeSort(int begin, int end);
		void				listInsertionSort(int begin, int end);
		void				listMergeSort(int begin, int end);
};

#endif
