/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:16:53 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 14:51:27 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <list>
#include <vector>
#include "Heuristics.hpp"
#include "Generator.hpp"
#include "GridPoint.hpp"

class State {
public:
	static int width;
	static int height;
	static std::u16string solution;
	static std::vector<int> order;

	enum Movement {
		None,
		Up,
		Right,
		Down,
		Left,
	};

	enum GridState {
		MissingNum,
		Impossible,
		Valid,
	};

	State(const std::u16string &data);
	State(State* parent, const Movement direction);

	std::list<State::Movement>	*get_movements() const;
	int 						get_distance() const;
	GridState 					is_solvable() const;
	bool 						is_final() const;
	State&						operator=(const State& o);


	static bool		pred_unordered_set(State* a, State* b);
	bool			operator==(State* b);
	static size_t	hash_unordered_set(State*a);
	static bool		comp_set(State* a, State* b);

	static State*	init(std::u16string data, int height, int width);

private:
	std::u16string	_data;
	score			_weight;
	int 			_distance;
	Movement 		_movement;
	State*			_parent;
};
