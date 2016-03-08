/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:43:29 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 19:28:36 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Parser.hpp"
#include "CliOptParser.hpp"
#include "Generator.hpp"
#include "Solver.hpp"

int		display_help(const char* path = "npuzzle")
{
	std::cout << "Usage: " << path << " [-w WIDTH] [-i ITERATION] [-s] [-u] [FILE]" << std::endl;
	std::cout << "if not params is give, programe should use stdin." << std::endl;
	return (0);
}

State	*parse_args(int ac, char **av)
{
	try
	{
		Parser				p;
		Parser::ParseResult	result;

		std::srand(std::time(0));
		if (ac == 1)
			result = p.parse_istream(std::cin);
		else if (ac == 2 && av[1][0] != '-')
			result = p.parse_file(av[1]);
		else
		{
			if (is_cmd_opt(av, av + ac, "-h"))
				exit(display_help(av[0]));
			if (is_cmd_opt(av, av + ac, "-i"))
				Generator::iteration = std::stoi(get_cmd_opt(av, av + ac, "-i"));

			if (is_cmd_opt(av, av + ac, "-w"))
				result.width = std::stoi(get_cmd_opt(av, av + ac, "-w"));
			else
				result.width = std::rand() % 16 + 3;
			if (result.width < 3)
			{
				std::cerr << av[0] << ": width too small" << std::endl;
				exit(1);
			}
			result.height = result.width; // TODO Make rectangular map
			State::init(result.width, result.width);
			if (is_cmd_opt(av, av + ac, "-s"))
				result.data = Generator::gen_solvable(result);
			else if (is_cmd_opt(av, av + ac, "-u"))
				result.data = Generator::gen_unsolvable(result);
			else
				result.data = Generator::gen_random(result);
		}
		State::init(result.width, result.width);
		return (new State(result.data));
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

int		main(int ac, char **av)
{
	State*	initial;

	initial = parse_args(ac, av);
	if (initial->is_solvable() == State::Valid)
	{
		std::cout << av[0] << ": Puzzle is solvable" << std::endl;
	}
	else if (initial->is_solvable() == State::Impossible)
	{
		std::cerr << av[0] << ": Puzzle is unsolvable" << std::endl;
		exit(1);
	}
	else
	{
		std::cerr << av[0] << ": Puzzle is broken" << std::endl;
		exit(1);
	}
	Solver		puzzle(initial);
	while (!puzzle.step().finished)
	{

	}
	return (0);
}
