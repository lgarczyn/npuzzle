/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CliOptParser.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 18:25:25 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:59:06 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <string>

char*	get_cmd_opt(char** begin, char** end, const std::string& option)
{
	while (begin != end)
	{
		if (!option.compare(*begin))
			return (*(++begin));
		++begin;
	}
	return 0;
}

bool	is_cmd_opt(char** begin, char** end, const std::string& option)
{
	while (begin != end)
	{
		if (!option.compare(*begin))
			return (true);
		++begin;
	}
	return (false);
}
