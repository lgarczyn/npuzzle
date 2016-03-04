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
#include "GridPoint.h"

int				State::width = 0;
int				State::height = 0;
std::u16string	State::solution;

State::State(const std::u16string &data) {
	_data = data;
	_weight = 0;
	_parent = NULL;
}

State::State(State* parent, const State::Movement direction) {
	_parent = parent;
	_weight = parent->_weight + 1;
	//do string shifting thing
	(void)direction;
}

State::GridState State::is_solvable() {
	std::u16string grid = _data;

	GridPoint posZero = GridPoint::GetPointFromIndex((int) grid.find(static_cast<char16_t >(0)), width);
	GridPoint destZero = GridPoint::GetPointFromIndex((int) solution.find(static_cast<char16_t >(0)), width);

	int distance = posZero.ManDistance(destZero);

	std::string::size_type index = 0;
	int moveCount = 0;
	while (index < grid.length()){
		char16_t& gridVal = grid[index];
		char16_t solutionVal = solution[index];

		if (gridVal != solutionVal)
		{
			std::string::size_type swapIndex = grid.find(solutionVal);
			if (swapIndex == std::string::npos)
			{
				return (State::GridState::MissingNum);
			}

			std::swap(gridVal, gridVal);
			moveCount++;
		}
		index++;
	}

	if (moveCount % 2 == distance % 2){
		return (State::GridState::Valid);
	}
	return (State::GridState::Impossible);
}
