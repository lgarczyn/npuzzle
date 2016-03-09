//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"
#include "State.hpp"

weighter Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;

score Heuristics::ManhattanDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    std::vector<int>&   finder = State::solution_finder;
    uint16_t val;

    (void)solution;
    for (int i = 0; i < length; i++)
    {
        val = data[i];
        int dist =  GridPoint::ManDistance(i, static_cast<int>(finder[val]), width);
        score += maxdist - dist;
    }
    return (score);
}

score Heuristics::SmartDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    std::vector<int>&   finder = State::solution_finder;
    uint16_t    val;

    (void)solution;
    for (int i = 0; i < length; i++)
    {
        val = data[i];
        int dist =  GridPoint::ManDistance(i, static_cast<int>(finder[val]), width);
        score += maxdist - dist;
    }
    val = 0;
    int tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), static_cast<int>(finder[val]), width);
    score += tmp;
    return (score);
}

score Heuristics::SuperSmartDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    for (int counter = 0; counter < length; counter++)
    {
        int i = State::order[counter];
        uint16_t val = data[i];
        int indexSolution = solution.find(val);
        int dist =  GridPoint::ManDistance(i, indexSolution, width);

        if (dist != 0)
        {
            int zeroDist = GridPoint::ManDistance(data.find(static_cast<char16_t>(0)), indexSolution, width);

            score += (maxdist - zeroDist) + (maxdist - dist);
            return (score);
        }
        else
        {
            score += 2 * maxdist;
        }
    }
    return (score);
}