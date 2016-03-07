/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 13:58:31 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include "GridPoint.hpp"

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

bool			State::operator<(const State* b) const 
{
	std::cout << "operator < of state" << std::endl;
	return  (_data == b->_data);
}

size_t	State::hash_unordered_set(const State* a)
{
	return  (std::hash<std::u16string>()(a->_data));
}

bool		State::comp_set(State* a, State* b)
{
	return  (a->_weight > b->_weight);
}
