/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 17:16:58 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include "GridPoint.hpp"
#include <iostream>

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
	_weight = std::rand();
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
