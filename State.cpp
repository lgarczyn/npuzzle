/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 19:22:49 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"

int					State::width = 0;
int					State::height = 0;
std::u16string		State::solution;
score				State::solution_score = 0;
score				State::initial_score = 0;
std::vector<int>	State::order;

State::State(const std::u16string &data) {
	_data = data;
	_weight = Heuristics::HeuristicFunction(_data, State::solution, State::width);
	_distance = 0;
	_movement = None;
	_parent = nullptr;
}

State::State(State* parent, const State::Movement direction) {
	_data = parent->_data;
	_parent = parent;
	_distance = parent->_distance + 1;
	_movement = direction;

	int		pos = _data.find(static_cast<char16_t>(0));
	int		w = State::width;
	int		h = State::height;
	switch (_movement)
	{
		case Up:
			if (pos - w >= 0)
				std::swap(_data.at(pos), _data.at(pos - w));
			break ;
		case Left:
			if (pos % w > 0)
				std::swap(_data.at(pos), _data.at(pos - 1));
			break ;
		case Right:
			if ((pos + 1) % w > 0)
				std::swap(_data.at(pos), _data.at(pos + 1));
			break ;
		case Down:
			if (pos + w < (w * h))
				std::swap(_data.at(pos), _data.at(pos + w));
			break ;
		case None:
			throw std::logic_error("None is not defined");
			break ;
	}
	_weight = Heuristics::HeuristicFunction(_data, State::solution, State::width);
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

const std::u16string&	State::get_data(void) const
{
	return (this->_data);
}

bool			State::operator<(const State* b) const
{
	std::cout << "operator < of state" << std::endl;
	return  (_data == b->_data);
}

void			State::set_parent(State* p)
{
	this->_parent = p;
}

State*			State::get_parent(void) const
{
	return (this->_parent);
}

void 			State::set_distance(int d)
{
	this->_distance = d;
}

score 						State::get_weight(void) const
{
	return (this->_weight);
}

void 						State::set_weight(score s)
{
	this->_weight = s;
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

	while (c <= max)
	{
		data[pos] = c;
		order[orderIndex++] = pos;
		++c;
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
	}
	return (order);
}

void			State::init(int width, int height)
{
	State::width = width;
	State::height = height;
	State::order = get_order(width, height);
	State::solution = Generator::gen_solution(width, height);
	State::solution_score = Heuristics::HeuristicFunction(State::solution, State::solution, width);
}
