/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:12:26 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:51:27 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

class Generator
{
	protected:
		static void				random_iteration(std::u16string& data);
	public:
		static int	iteration;

		static std::u16string	gen_solution(void);
		static std::u16string	gen_solvable(void);
		static std::u16string	gen_unsolvable(void);
		static std::u16string	gen_random(void);
};
