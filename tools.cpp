/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 19:05:57 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 19:39:17 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include "State.hpp"

void split(const std::string& str,
		std::vector<std::string>& tokens,
		const std::string& delimiters)
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

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(),
			[](char c) { return !std::isdigit(c); }) == s.end();
}

void	print_map(const std::u16string& d)
{
	int		width = State::width;
	int		height = State::height;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			std::string val = std::to_string(d.at(x + y * height));
			std::cout << val << std::string(4 - val.length(), ' ');
		}
		std::cout << std::endl;
	}
}
