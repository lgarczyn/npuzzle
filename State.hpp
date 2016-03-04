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

#include <string>

#pragma once

class State {
private:
	std::u16string	_data;
	int				_weight;
	State*			_parent;

public:
	static int width;
	static int height;
	static u16string solution;

	enum Movement {
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

		bool 	isSolvable();
		State&	operator=(const State& o);
};
