/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:16:46 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 17:57:16 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Generator.hpp"

std::u16string	Generator::gen_solution(void)
{
	int				w = State::width;
	int				h = State::height;
	char16_t		max = w * h;
	char16_t		c = 1;
	int				pos = 0;
	State::Movement	dir = State::Right;
	std::u16string	data(w * h, static_cast<char16_t>('\0'));
	
	while (c != max)
	{
		data[pos] = c;
		switch (dir)
		{
			case State::Right:
				++pos;
				if ((pos + 1) % w == 0 || data[pos + 1])
					dir = State::Down;
				break ;
			case State::Left:
				--pos;
				if (pos % w == 0 || data[pos - 1])
					dir = State::Up;
				break ;
			case State::Up:
				pos -= w;
				if (pos < w || data[pos - w])
					dir = State::Right;
				break ;
			case State::Down:
				pos += w;
				if (pos >= w * (h - 1) || data[pos + w])
					dir = State::Left;
				break ;
		}
		++c;
	}
	return (data);
}
