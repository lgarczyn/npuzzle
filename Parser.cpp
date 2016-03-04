/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:03:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 16:25:47 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <fstream>

#include <iostream>
#include <regex>
#include <string>
#include <algorithm>

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


#include <vector>
void split(const std::string& str,
		std::vector<std::string>& tokens,
		const std::string& delimiters = " ")
{
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

	tokens.clear();
	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
}

State*			Parser::parse_istream(std::istream& file)
{
	State*						res;
	std::string					line;
	std::vector<std::string>	tab;
	std::u16string				data;

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
					std::cerr << "TODO: Throw" << std::endl; // TODO
				State::width = std::stoi(tab[0]);
				State::height = State::width;
			}
			else
			{
				for (auto s:tab)
					data.push_back(std::stoi(s));
			}
		}
	}
	res = new State(data);
	return (res);
}
