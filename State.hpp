/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:16:53 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/17 17:43:59 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
#include "Heuristics.hpp"
#include "Generator.hpp"
#include "GridPoint.hpp"

class State {
public:
	static int width;
	static int height;
	static int size;
	static std::u16string solution;
	static std::vector<int>	solution_finder;
	static score initial_score;
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

		std::vector<State::Movement>	*get_movements() const;
		Movement						get_movement() const;
		int 							get_distance() const;
		score 							get_weight() const;
		void 							set_weight(score s);
		const std::u16string&			get_data() const;
		void 							set_distance(int d);
		GridState 						is_solvable() const;
		bool 							is_final() const;
		void							set_parent(State* p);
		State*							get_parent(void) const;

		bool						operator<(const State* b) const;
		static void					init(int width, int height);

	private:
		std::u16string	_data;
		score			_weight;
		int 			_distance;
		Movement 		_movement;
		State*			_parent;
};

std::ostream& operator<< (std::ostream& s, const State::Movement c);

struct custom_hash
{
public:
	size_t operator()(const State* x) const noexcept;
};

struct custom_equal_to
{
public:
	bool operator()(const State* a, const State* b) const noexcept;
};

struct custom_less
{
public:
	bool operator()(const State* a, const State* b);
};
