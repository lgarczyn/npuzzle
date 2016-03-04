//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#ifndef NPUZZLE_HEURISTICS_H
#define NPUZZLE_HEURISTICS_H

#include <string>

using score=long int;
using long int (*weighter)(const uint16_t& data, int width);

static class Heuristics
{
public:
    score ManhattanDistance(const uint16_t& data, int width);
};


#endif //NPUZZLE_HEURISTICS_H
