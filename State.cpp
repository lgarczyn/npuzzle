/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 16:30:30 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

int				State::width = 0;
int				State::height = 0;
std::u16string	State::solution;

State::State(const std::u16string &data) {
	_data = data;
	_weight = 0;
	_distance = 0;
	_movement = None;
	_parent = NULL;
}

State::State(State* parent, const State::Movement direction) {
	_data = parent->_data;
	_parent = parent;
	_weight = 0;
	_distance = parent->_distance + 1;
	_movement = direction;
	//TODO string shifting thing
	//TODO calculate weight
	(void)direction;
}

std::list<State::Movement>* State::get_movements() const {
	std::list<State::Movement>* movements = new std::list<State::Movement>(_distance);
	const State* node = this;

	while (node) {
		movements->push_back(node->_movement);
		node = node->_parent;
	}
	movements->reverse();
	return (movements);
}

int State::get_distance() const
{
	return (_distance);
}

State::GridState State::is_solvable() const {
	std::u16string grid = _data;

	GridPoint posZero = GridPoint::GetPointFromIndex((int) grid.find(static_cast<char16_t >(0)), width);
	GridPoint destZero = GridPoint::GetPointFromIndex((int) solution.find(static_cast<char16_t >(0)), width);

	int distance = posZero.ManDistance(destZero);

	std::string::size_type index = 0;
	int moveCount = 0;
	while (index < grid.length()){
		char16_t solutionVal = solution[index];

		if (grid[index] != solutionVal)
		{
			std::string::size_type swapIndex = grid.find(solutionVal, index);
			if (swapIndex == std::string::npos)
			{
				return (State::GridState::MissingNum);
			}

			std::swap(grid[index], grid[swapIndex]);
			moveCount++;
		}
		index++;
	}

	if (moveCount % 2 == distance % 2){
		return (State::GridState::Valid);
	}
	return (State::GridState::Impossible);
}

bool State::is_final() const {
	return (_data == solution);
}

bool		State::pred_unordered_set(State* a, State* b)
{
	return  (a == b);
}

bool			State::operator==(State* b)
{
	return  (_data == b->_data);
}

size_t	State::hash_unordered_set(State*a)
{
	return  (std::hash<std::string>()(a->_data));
}

bool		State::comp_set(State* a, State* b)
{
	return  (a->_weight > b->_weight);
}

std::vector<int> get_order(int w, int h)
{
	int orderIndex = 0;
	int				max = w * h;
	std::vector<int> order = std::vector<int>(max);
	char16_t		c = 1;
	int				pos = 0;
	State::Movement	dir = State::Right;
	std::u16string	data(max, static_cast<char16_t>('\0'));

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
			default:
				break;
		}
		++c;
		order[orderIndex++] = pos;
	}
	return (order);
}

void State::init(int width, int height)
{
	State::width = width;
	State::height = height;
	State::order = get_order(width, height);
	State::solution = Generator::gen_solution();
}
