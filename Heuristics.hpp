//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#pragma once

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::string& data, int width);
using swapper = score (*)(std::string& data, int width, int prev_pos, int new_pos);

class Heuristics
{
public:
    static score	ManhattanDistance(const std::string& data, int width);
	static score	LinearConflict(const std::string& data, int width);
    static score	SuperSmartDistance(const std::string& data, int width);

	static score 	ManhattanDistanceSwap(std::string& data, int width, int pos_a, int pos_b);
	static score	SmartDistanceSwap(std::string& data, int width, int i_zero, int i_val);
	static score	SuperSmartDistanceSwap(std::string& data, int width, int pos_a, int pos_b);

	static weighter	HeuristicFunction;
	static swapper HeuristicFunctionSwapper;
};
