/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 19:05:00 by edelangh          #+#    #+#             */
/*   Updated: 2016/03/04 19:07:18 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

void split(const std::string& str,
		std::vector<std::string>& tokens,
		const std::string& delimiters = " ");
bool is_number(const std::string& s);
