/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:03:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/18 17:42:10 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "tools.h"
#include <fstream>
#include <regex>

Parser::ParseResult::ParseResult():data(), width(0), shouldGenerate(false), forget(), search_step(0){};
bool	Parser::allow_rectangle = false;

Parser::ParseResult	Parser::parse_file(const char* file_src)
{
	std::ifstream	file(file_src, std::ifstream::in);
	ParseResult		res;

	if (file.good())
	{
		res = this->parse_istream(file);
		file.close();
	}
	else
	{
		throw std::logic_error(std::string(file_src) + ": Bad file path");
	}
	return (res);
}

Parser::ParseResult		Parser::parse_istream(std::istream& file)
{
	ParseResult					res;
	std::string					line;
	std::vector<std::string>	tab;
	int							w;
	int							h = 0;

	while (std::getline(file, line))
	{
		if (line.find("#") != std::string::npos)
			line = line.substr(0, line.find("#"));
		std::replace(line.begin(), line.end(), '\t', ' ');
		split(line, tab);
		if (tab.size() > 0)
		{
			if (res.width == 0)
			{
				if (tab.size() != 1)
					throw std::logic_error("Bad size initialization");
				if (!is_number(tab[0]))
					throw std::logic_error("Size is not a number: " + tab[0]);
				w = std::stoi(tab[0]);
				res.width = w;
				if (w <= 0 || w >= 17)
					throw std::logic_error("Bad size: 0 < size < 17");
			}
			else
			{
				if (tab.size() != static_cast<unsigned long>(w))
					throw std::logic_error("Bad line width");
				for (auto s:tab)
				{
					if (!is_number(s))
						throw std::logic_error("Is not a number: " + tab[0]);
					res.data.push_back(std::stoi(s));
				}
				++h;
			}
		}
	}
	res.height = h;
	if (h < 2 || (!allow_rectangle && res.data.length() != static_cast<unsigned long>(w * w)))
		throw std::logic_error("Bad line number");
	return (res);
}
