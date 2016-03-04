/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:03:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 19:07:01 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include "tools.h"
#include <fstream>
#include <regex>

State*			Parser::parse_file(const char* file_src)
{
	std::ifstream	file(file_src, std::ifstream::in);
	State*			res = nullptr;

	if (file.good())
	{
		res = this->parse_istream(file);
		file.close();
	}
	return (res);
}

State*			Parser::parse_istream(std::istream& file)
{
	State*						res;
	std::string					line;
	std::vector<std::string>	tab;
	std::u16string				data;
	int							w;

	while (std::getline(file, line))
	{
		if (line.find("#") != std::string::npos)
			line = line.substr(0, line.find("#"));
		std::replace(line.begin(), line.end(), '\t', ' ');
		split(line, tab);
		if (tab.size() > 0)
		{
			if (State::width == 0)
			{
				if (tab.size() != 1)
					throw std::logic_error("Bad size initialization");
				if (!is_number(tab[0]))
					throw std::logic_error("Size is not a number: " + tab[0]);
				w = std::stoi(tab[0]);
				State::width = w;
				State::height = w;
				if (w <= 0 || w >= 256)
					throw std::logic_error("Bad size: 0 < size < 256");
			}
			else
			{
				if (tab.size() != static_cast<unsigned long>(w))
					throw std::logic_error("Bad line width");
				for (auto s:tab)
				{
					if (!is_number(s))
						throw std::logic_error("Is not a number: " + tab[0]);
					data.push_back(std::stoi(s));
				}
			}
		}
	}
	if (data.length() != static_cast<unsigned long>(w * w))
		throw std::logic_error("Bad line number");
	res = new State(data);
	return (res);
}
