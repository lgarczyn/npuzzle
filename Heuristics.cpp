//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"
#include "State.hpp"
#include <algorithm>

weighter	Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;
swapper		Heuristics::HeuristicFunctionSwapper = Heuristics::ManhattanDistanceSwap;

score Heuristics::ManhattanDistance(const std::u16string& data, int width)
{
	int				 score = 0;
	int				 length = data.length();
	std::vector<int>&   finder = State::solution_finder;
	uint16_t			val;

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

score Heuristics::ManhattanDistanceSwap(std::u16string& data, int width, int prev_pos, int next_pos)
{
	int target_pos = State::solution_finder[data[prev_pos]];

	int prev_score = GridPoint::ManDistance(target_pos, prev_pos, width);
	int next_score = GridPoint::ManDistance(target_pos, next_pos, width);

	return (next_score - prev_score);
}

score Heuristics::SmartDistanceSwap(std::u16string& data, int width, int prev_pos, int next_pos)
{
	std::vector<int>&   finder = State::solution_finder;
	score		score = 0;
	int			maxdist = width + width - 2;
	uint16_t	val;
	int			dist;
	int			tmp;

	{ // Substract old score
		val = data[prev_pos];
		dist = GridPoint::ManDistance(prev_pos, finder[val], width);
		score -= maxdist - dist;
		val = data[next_pos];
		dist = GridPoint::ManDistance(next_pos, finder[val], width);
		score -= maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score -= tmp;
	}
	std::swap(data.at(prev_pos), data.at(next_pos));
	{ // Add new score
		val = data[prev_pos];
		dist = GridPoint::ManDistance(prev_pos, finder[val], width);
		score += maxdist - dist;
		val = data[next_pos];
		dist = GridPoint::ManDistance(next_pos, finder[val], width);
		score += maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score += tmp;
	}
	return (score);
}

score Heuristics::SmartDistance(const std::u16string& data, int width)
{
	score score = 0;
	int maxdist = width + width - 2;
	int length = data.length();
	std::vector<int>&   finder = State::solution_finder;
	uint16_t	val;

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

score Heuristics::SuperSmartDistanceSwap(std::u16string& data, int width, int prev_pos, int next_pos)
{
	std::vector<int>&   finder = State::solution_finder;
	score		score = 0;
	int			maxdist = width + width - 2;
	uint16_t	val;
	int			dist;
	int			tmp;

	{ // Substract old score
		val = data[prev_pos];
		dist = GridPoint::ManDistance(prev_pos, finder[val], width);
		score -= maxdist - dist;
		val = data[next_pos];
		dist = GridPoint::ManDistance(next_pos, finder[val], width);
		score -= maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score -= tmp;
	}
	std::swap(data.at(prev_pos), data.at(next_pos));
	{ // Add new score
		val = data[prev_pos];
		dist = GridPoint::ManDistance(prev_pos, finder[val], width);
		score += maxdist - dist;
		val = data[next_pos];
		dist = GridPoint::ManDistance(next_pos, finder[val], width);
		score += maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score += tmp;
	}
	return (score);
}

score Heuristics::SuperSmartDistance(const std::u16string& data, int width)
{
	int score = 0;
	int maxdist = width + width - 2;
	int length = data.length();
	std::vector<int>&   finder = State::solution_finder;
	const std::u16string&	solution = State::solution;
	uint16_t	val;

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
