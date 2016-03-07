/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:16:53 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 14:01:30 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <list>
#include "Heuristics.hpp"

#pragma once

class State {
	public:
		static int width;
		static int height;
		static std::u16string solution;

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
		bool			operator<(const State* b) const;
		size_t	hash_unordered_set(const State* a);
		static bool		comp_set(State* a, State* b);


	private:
		std::u16string	_data;
		score			_weight;
		int 			_distance;
		Movement 		_movement;
		State*			_parent;
};

// TODO: it's juste a test, need to be realy do
#include <iostream>
template<>
struct std::hash<State*>
{
	size_t operator()(const State* x) const noexcept
	{
		std::cout << "hash state" << std::endl;
		(void)x;
		return (0);
	}
};

template<>
struct std::less<State*>
{
	bool operator()(const State* a, const State* b)
	{
		std::cout << "less on state" << std::endl;
		return (a < b);
	}
};
