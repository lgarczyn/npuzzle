/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:43:29 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/11 11:07:14 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Parser.hpp"
#include "CliOptParser.hpp"
#include "Generator.hpp"
#include "Solver.hpp"
#include "tools.h"

int		display_help(const char* path = "npuzzle")
{
	std::cout << "Usage: " << path << " [-h] [-w WIDTH] [-i ITERATION] [-s] [-u] [-f1] [-f2] [-f3] [-c MIN_STEP] [-m FILE]" << std::endl;
	std::cout << "if no map is give, npuzzle should use stdin." << std::endl;
	return (0);
}

Parser::ParseResult	get_result(int ac, char **av)
{
	Parser::ParseResult	result;
	Parser				p;

	if (is_cmd_opt(av, av + ac, "-m")) {
		std::cout << "READ M" << std::endl;
		result = p.parse_file(get_cmd_opt(av, av + ac, "-m"));
	}
	else if (is_cmd_opt(av, av + ac, "-w")) {
		result.width = std::stoi(get_cmd_opt(av, av + ac, "-w"));
		if (result.width < 3) {
			std::cerr << av[0] << ": width too small" << std::endl;
			exit(1);
		}
		result.height = result.width; // TODO Make rectangular map
		result.shouldGenerate = true;
	}
	else
		result = p.parse_istream(std::cin);
	return (result);
}

Parser::ParseResult	parse_args(int ac, char **av)
{
	Parser::ParseResult result;
	try {
		std::srand(std::time(0));
		if (is_cmd_opt(av, av + ac, "-h"))
			exit(display_help(av[0]));
		if (is_cmd_opt(av, av + ac, "-f1"))
		{
			Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;
			Heuristics::HeuristicFunctionSwaper = Heuristics::ManhattanDistanceSwap;
		}
		if (is_cmd_opt(av, av + ac, "-f2"))
		{
			Heuristics::HeuristicFunction = Heuristics::SmartDistance;
			Heuristics::HeuristicFunctionSwaper = Heuristics::SmartDistanceSwap;
		}
		if (is_cmd_opt(av, av + ac, "-f3"))
		{
			Heuristics::HeuristicFunction = Heuristics::SuperSmartDistance;
			Heuristics::HeuristicFunctionSwaper = Heuristics::SuperSmartDistanceSwap;
		}
		result = get_result(ac, av);
		if (is_cmd_opt(av, av + ac, "-i"))
			Generator::iteration = std::stoi(get_cmd_opt(av, av + ac, "-i"));

		if (is_cmd_opt(av, av + ac, "-c"))
			sscanf(get_cmd_opt(av, av + ac, "-c"), "%zu", &result.search_step);
		State::init(result.width, result.width);

		if (result.shouldGenerate)
		{
			if (is_cmd_opt(av, av + ac, "-s"))
				result.data = Generator::gen_solvable(result);
			else if (is_cmd_opt(av, av + ac, "-u"))
				result.data = Generator::gen_unsolvable(result);
			else
				result.data = Generator::gen_random(result);
		}
		return (result);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		exit(1);
	}
}

int		main(int ac, char **av)
{
	State*					initial;
	Parser::ParseResult		result;

	result = parse_args(ac, av);
	initial = new State(result.data);
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
	std::cout << "Start" << std::endl;
	print_map(initial->get_data());
	Solver		puzzle(initial);
	Solver::Result	res(0,0);
	size_t 	it;
	int 	niv;

	it = 0;
	do {
		while (!(res = puzzle.step()).finished)
		{
			if (it % 10000 == 0)
			{
				niv = ((res.actual_state->get_weight() - State::initial_score) * 100.0f) / (State::solution_score - State::initial_score);
				std::cout << "Iteration count: " << it << std::endl;
				std::cout << "Solution [score: " << res.actual_state->get_weight() << "]: " << niv << "%" << std::endl;
				print_map(res.actual_state->get_data());
			}
			++it;
		}
		niv = ((res.actual_state->get_weight() - State::initial_score) * 100.0f) / (State::solution_score - State::initial_score);
		std::cout << "-- Iteration count: " << it << std::endl;
		std::cout << "-- Solution: " << niv << "%" << std::endl;
		std::cout << "-- Move count: " << res.movements->size() << std::endl;
		print_map(res.actual_state->get_data());
	} while ((result.search_step && result.search_step < res.movements->size()));
	return (0);
}
