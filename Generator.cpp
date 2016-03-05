/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Generator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 17:16:46 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 19:18:48 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Generator.hpp"
#include <cstdlib>

int	Generator::iteration = 42;

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
void			Generator::random_iteration(std::u16string& data)
{
	int		pos;
	int		w = State::width;
	int		h = State::height;

	for (auto i = iteration; i > 0; --i)
	{
		pos = data.find(static_cast<char16_t>(0));
		switch (std::rand() & 3)
		{
			case 0:
				if (pos - w >= 0)
					std::swap(data.at(pos), data.at(pos - w));
				break ;
			case 1:
				if (pos % w > 0)
					std::swap(data.at(pos), data.at(pos - 1));
				break ;
			case 2:
				if ((pos + 1) % w > 0)
					std::swap(data.at(pos), data.at(pos + 1));
				break ;
			case 3:
				if (pos + w < (w * h))
					std::swap(data.at(pos), data.at(pos + w));
				break ;
		}
	}
}

std::u16string	Generator::gen_solvable(void)
{
	std::u16string data;

	data = gen_solution();
	random_iteration(data);
	return (data);
}

std::u16string	Generator::gen_unsolvable(void)
{
	std::u16string data;

	data = gen_solution();
	std::swap(data.at(0), data.at(1));
	random_iteration(data);
	return (data);
}

std::u16string	Generator::gen_random(void)
{
	if (std::rand() & 1)
		return (gen_solvable());
	else
		return (gen_unsolvable());
}
