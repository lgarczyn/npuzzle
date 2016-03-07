//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#ifndef NPUZZLE_HEURISTICS_H
#define NPUZZLE_HEURISTICS_H

#include <string>
#include "GridPoint.hpp"

using score = long int;
using weighter = score (*)(const std::u16string& data, const std::u16string& solution, int width);

class Heuristics
{
public:
    score ManhattanDistance(const std::u16string& data, const std::u16string& solution, int width);
    score SmartDistance(const std::u16string& data, const std::u16string& solution, int width);
    score SuperSmartDistance(const std::u16string& data, const std::u16string& solution, int width);
};


#endif //NPUZZLE_HEURISTICS_H
