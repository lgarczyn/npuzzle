//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"

weighter Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;

score Heuristics::ManhattanDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    for (int i = 0; i < length; i++)
    {
        uint16_t val = data[i];
        int dist =  GridPoint::ManDistance(i, static_cast<int>(solution.find(val)), width);
        score += maxdist - dist;
    }
    return (score);
}

#include "State.hpp"

score Heuristics::SmartDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    for (int i = 0; i < length; i++)
    {
        uint16_t val = data[i];
        // TODO Use State::order
        int dist =  GridPoint::ManDistance(i, static_cast<int>(solution.find(val)), width);
        score += maxdist - dist;
        if (dist != 0)
        {
            return (score);
        }
    }
    return (score);
}

score Heuristics::SuperSmartDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    for (int i = 0; i < length; i++)
    {

        uint16_t val = data[i];

        // int indexSolution =  solution.find(val);
        int dist =  GridPoint::ManDistance(i, solution.find(val), width);

        if (dist != 0)
        {
            int zeroDist = GridPoint::ManDistance(data.find(static_cast<char16_t>(0)), solution.find(val), width);

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
