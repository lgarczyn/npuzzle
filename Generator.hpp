/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:12:26 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 19:24:09 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "State.hpp"
#include "Parser.hpp"
#include <cstdlib>

class Generator
{
protected:
	static void				random_iteration(std::string& data, int w, int h);
public:
	static int	iteration;

	Parser lol;
	enum GenerationKind
	{
		solved,
		solvable,
		unsolvable,
		random
	};

	static std::string	gen_solution(int w, int h);
	static std::string	gen_solvable(Parser::ParseResult& p);
	static std::string	gen_unsolvable(Parser::ParseResult& p);
	static std::string	gen_random(Parser::ParseResult& p);
//	static std::string	gen(GenerationKind kind);
};
