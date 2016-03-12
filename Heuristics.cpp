//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"
#include "State.hpp"

weighter Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;

score Heuristics::ManhattanDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int                 score = 0;
    int                 length = data.length();
    std::vector<int>&   finder = State::solution_finder;
    uint16_t            val;

    (void)solution;
    for (int i = 0; i < length; i++)
    {
        val = data[i];
        if (val)
        {
            int dist =  GridPoint::ManDistance(i, finder[val], width);
            score += dist;
        }
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
        int dist =  GridPoint::ManDistance(i, finder[val], width);
        score += maxdist - dist;
    }
    val = 0;
    int tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
    score += tmp;
    return (score);
}

score Heuristics::SuperSmartDistance(const std::u16string& data, const std::u16string& solution, int width)
{
    int score = 0;
    int maxdist = width + width - 2;
    int length = data.length();
    std::vector<int>&   finder = State::solution_finder;
    uint16_t    val;

    for (int i = 0; i < length; i++)
    {
        val = data[i];
        int dist =  GridPoint::ManDistance(i, finder[val], width);
        score += maxdist - dist;
    }

    int finishedIndex = 0;
    for (int i = 0; i < length; i++)
    {
        int index = State::order[i];
        if (data[index] != solution[index])
            break;
        finishedIndex++;
    }
    finishedIndex = State::order[finishedIndex];

    val = solution[finishedIndex];
    int targetIndex = data.find(val);
    val = 0;
    int zeroIndex = data.find(val);

    int distZero = GridPoint::ManDistance(targetIndex, zeroIndex, width);
    distZero -= 4;

    int smartScore = maxdist - distZero;

    if (distZero)
    {
        int distTarget = GridPoint::ManDistance(targetIndex, finishedIndex, width);
        smartScore += maxdist - distTarget;
    }
    return (score + smartScore * 2);
}
