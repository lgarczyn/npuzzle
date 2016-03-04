/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:43:29 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 17:57:38 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include "Parser.hpp"
#include "State.hpp"
#include "Generator.hpp"

State	*init(int ac, char **av)
{
	Parser	p;
	State	*initial;

	try
	{
		if (ac == 1)
			initial = p.parse_istream(std::cin);
		else
			initial = p.parse_file(av[1]);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	State::solution = Generator::gen_solution();
	return (initial);
}

int		main(int ac, char **av)
{
	State*	initial;

	initial = init(ac, av);
	if (!initial->is_solvable())
	{
		std::cerr << av[0] << ": Puzzle is unsolvable" << std::endl;
		exit(1);
	}
	return (0);
}
