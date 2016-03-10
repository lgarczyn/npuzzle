//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#ifndef NPUZZLE_HEURISTICS_H
#define NPUZZLE_HEURISTICS_H

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::u16string& data, int width);

class Heuristics
{
public:
    static score	ManhattanDistance(const std::u16string& data, int width);
    static score	SmartDistance(const std::u16string& data, int width);
    static score	SuperSmartDistance(const std::u16string& data, int width);

	static score	SmartDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b);

	static weighter	HeuristicFunction;
};


#endif //NPUZZLE_HEURISTICS_H
