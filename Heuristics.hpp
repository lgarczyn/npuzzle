//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#pragma once

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::string& data, int width, int height);

class Heuristics
{
public:
    static score	ManhattanDistance(const std::string& data, int width, int height);
	static score	LinearConflict(const std::string& data, int width, int height);
    static score	SuperSmartDistance(const std::string& data, int width, int height);

	static weighter	HeuristicFunction;
};
