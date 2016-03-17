/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 14:52:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/07 19:17:56 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <fstream>

class	Parser
{
	private:
	public:
		class ParseResult
		{
		public:
			std::string data;
			int		width;
			int		height;
			bool	shouldGenerate;
			size_t 	search_step;

			ParseResult();
		};

		Parser() {}
		ParseResult parse_file(const char* file_src);
		ParseResult parse_istream(std::istream& file);
};
