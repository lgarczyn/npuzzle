/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:43:29 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:52:50 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Parser.hpp"
#include "CliOptParser.hpp"
#include "Generator.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

int		display_help(const char* path = "npuzzle")
{
	std::cout << "Usage: " << path << " [-w WIDTH] [-i ITERATION] [-s] [-u] [FILE]" << std::endl;
	std::cout << "if not params is give, programe should use stdin." << std::endl;
	return (0);
}

State	*init(int ac, char **av)
{
	Parser	p;
	State	*initial;

	std::srand(std::time(0));
	try
	{
		if (ac == 1)
			initial = p.parse_istream(std::cin);
		else if (ac == 2)
			initial = p.parse_file(av[1]);
		else
		{
			if (is_cmd_opt(av, av + ac, "-h"))
				exit(display_help(av[0]));
			if (is_cmd_opt(av, av + ac, "-i"))
				Generator::iteration = std::stoi(get_cmd_opt(av, av + ac, "-i"));
			if (is_cmd_opt(av, av + ac, "-w"))
				State::width = State::height = std::stoi(get_cmd_opt(av, av + ac, "-w"));
			else
				State::width = State::height = std::rand() % 16 + 3;
			if (State::width < 3)
			{
				std::cerr << av[0] << ": width to small" << std::endl;
				exit(1);
			}
			if (is_cmd_opt(av, av + ac, "-s"))
				initial = new State(Generator::gen_solvable());
			else if (is_cmd_opt(av, av + ac, "-u"))
				initial = new State(Generator::gen_unsolvable());
			else
				initial = new State(Generator::gen_random());
		}
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
	return (0);
}
