//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#pragma once

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::string& data, int width);

class Heuristics
{
public:
    static score	ManhattanDistance(const std::string& data, int width);
	static score	LinearConflict(const std::string& data, int width);
    static score	SuperSmartDistance(const std::string& data, int width);

	static weighter	HeuristicFunction;
};
