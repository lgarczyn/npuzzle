/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:18:52 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 14:25:09 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "State.hpp"
#include "GridPoint.h"

int		State::width = 0;
int		State::height = 0;

State::State(const std::u16string &data) {
	_data = data;
	_weight = 0;
	_parent = NULL;
}

State::State(State* parent, const State::Movement direction) {
	_parent = parent;
	_weight = parent->_weight + 1;
	//do string shifting thing
}

bool State::IsSolvable() {
	std::u16string solve = _data;

	int index = 0;
	GridPoint posZero((int) solve.find(0), width, height);
	GridPoint destZero((int) solution.find(0), width, height);

	while (index < solve.length()) {

	}

	return (false);
}
