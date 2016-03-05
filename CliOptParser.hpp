/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CliOptParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 18:38:58 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/05 18:39:12 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

bool	is_cmd_opt(char** begin, char** end, const std::string& option);
char*	get_cmd_opt(char** begin, char** end, const std::string& option);
