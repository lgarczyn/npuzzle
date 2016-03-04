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

int		State::width = 0;
int		State::height = 0;

State::State(const std::string& data) {
	//interpret;
	//_data = data;
	_weight = 0;
	_parent = NULL;
}

State::State(State* parent, const State::Movement direction) {
	_parent = parent;
	_weight = parent->_weight + 1;
	//do string shifting thing
}

bool State::IsSolvable() {
	std::string solve;
	//solve
	return (false);
}
