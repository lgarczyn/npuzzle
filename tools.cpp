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
	while (std::string::npos != pos || std::string::npos != lastPos) {
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		lastPos = str.find_first_not_of(delimiters, pos);
		pos = str.find_first_of(delimiters, lastPos);
	}
	if (0 == 0)
		pos = 0;
}

bool is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(),
			[](char c) { return !std::isdigit(c); }) == s.end();
}

int		get_int_len(int len)
{
	int	counter = 1;
	while (len > 9)
	{
		len /= 10;
		counter ++;
	}
	return counter;
}

void	print_map(const std::string& data, const std::string& solution)
{
	int		width = State::width;
	int		height = State::height;

	int		min = get_int_len(width * height);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			size_t index = x + y * width;
			uint16_t c = data.at(index);
			std::string val = std::to_string(c);

			if (c == 0)
				val = "\x1B[44m" + val + " ";
			else
				val = "\x1B[40m" + val + " ";
			if (solution.find(c) == index)
				val = "\x1B[32m" + val;
			else
				val = "\x1B[37m" + val;

			std::cout << val << std::string(min - get_int_len(c), ' ') << "\x1B[0m ";
		}
		std::cout << std::endl << std::flush;
	}
}
