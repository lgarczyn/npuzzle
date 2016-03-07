/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:16:53 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 17:55:18 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <list>
#include "Heuristics.hpp"
#include <vector>
#include <functional>

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
		score 						get_weight() const;
		void 						set_weight(score s);
		const std::u16string&		get_data() const;
		void 						set_distance(int d);
		GridState 					is_solvable() const;
		bool 						is_final() const;
		void						set_parent(State* p);
		State*						get_parent(void) const;

		bool						operator<(const State* b) const;

	private:
		std::u16string	_data;
		score			_weight;
		int 			_distance;
		Movement 		_movement;
		State*			_parent;
};

template<>
struct std::hash<State*>
{
	size_t operator()(const State* x) const noexcept
	{
		std::hash<std::u16string>	hash;
		return (hash(x->get_data()));
	}
};
#include <iostream>
template<>
struct std::equal_to<State*>
{
	size_t operator()(const State* a, const State* b) const noexcept
	{
		return (a->get_data() == b->get_data());
	}
};

template<>
struct std::less<State*>
{
	bool operator()(const State* a, const State* b)
	{
		return (a->get_weight() > b->get_weight());
	}
};
