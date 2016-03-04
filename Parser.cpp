/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 15:03:37 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 15:06:13 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"
#include <fstream>

State*	Parser::parse_file(const char* file_src)
{
	std::ifstream	file(file_src, std::ifstream::in);
	State*			res = nullptr;

	if (file.good())
		res = this->parse_istream(file);
	return (res);
}

State*	Parser::parse_istream(std::istream& file)
{
	return (nullptr);
}
