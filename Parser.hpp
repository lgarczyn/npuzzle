/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:52:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 15:04:02 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "State.hpp"

class	Parser
{
	private:
	public:
		Parser() {}
		State	*parse_file(const char* file_src);
		State	*parse_istream(std::istream& file);
};
