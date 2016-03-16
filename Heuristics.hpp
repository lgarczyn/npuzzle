//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#ifndef NPUZZLE_HEURISTICS_H
#define NPUZZLE_HEURISTICS_H

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::u16string& data, int width);
using swapper = score (*)(std::u16string& data, int width, int prev_pos, int new_pos);

class Heuristics
{
public:
    static score	ManhattanDistance(const std::u16string& data, int width);
	static score	LinearConflict(const std::u16string& data, int width);
    static score	SuperSmartDistance(const std::u16string& data, int width);

	static score 	ManhattanDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b);
	static score	SmartDistanceSwap(std::u16string& data, int width, int i_zero, int i_val);
	static score	SuperSmartDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b);

	static weighter	HeuristicFunction;
	static swapper HeuristicFunctionSwapper;
};


#endif //NPUZZLE_HEURISTICS_H
