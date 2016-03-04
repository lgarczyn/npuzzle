/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   State.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:16:53 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 14:23:34 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

class State {
	private:
		std::u16string	_data;
		int				_weight;
		State			*_parent;

	public:
		static int width;
		static int height;

		enum Movement {
			Up,
			Right,
			Down,
			Left,
		};

		State(const std::string& data);
		State(State* parent, const Movement direction);

		bool IsSolvable();
		State&	operator=(const State& o);;
};
