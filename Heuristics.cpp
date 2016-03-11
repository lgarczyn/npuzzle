//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"
#include "State.hpp"
#include <algorithm>

weighter	Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;
swaper		Heuristics::HeuristicFunctionSwaper = Heuristics::ManhattanDistanceSwap;

score Heuristics::ManhattanDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b)
{
	score	score = 0;
	int maxdist = width + width - 2;
	std::vector<int>&   finder = State::solution_finder;
	uint16_t	val;
	int			dist;

	{ // Substract old score
		val = data[pos_a];
		dist =  GridPoint::ManDistance(pos_a, finder[val], width);
		score -= maxdist - dist;
		val = data[pos_b];
		dist =  GridPoint::ManDistance(pos_b, finder[val], width);
		score -= maxdist - dist;
	}
	std::swap(data.at(pos_a), data.at(pos_b));
	{ // Add new score
		val = data[pos_a];
		dist =  GridPoint::ManDistance(pos_a, finder[val], width);
		score += maxdist - dist;
		val = data[pos_b];
		dist =  GridPoint::ManDistance(pos_b, finder[val], width);
		score += maxdist - dist;
	}
	return (score);
}

score Heuristics::ManhattanDistance(const std::u16string& data, int width)
{
	score score = 0;
	int maxdist = width + width - 2;
	int length = data.length();
	std::vector<int>&   finder = State::solution_finder;
	uint16_t val;

	for (int i = 0; i < length; i++)
	{
		val = data[i];
		int dist =  GridPoint::ManDistance(i, finder[val], width);
		score += maxdist - dist;
	}
	return (score);
}

score Heuristics::SmartDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b)
{
	std::vector<int>&   finder = State::solution_finder;
	score		score = 0;
	int			maxdist = width + width - 2;
	uint16_t    val;
	int			dist;
	int			tmp;

	{ // Substract old score
		val = data[pos_a];
		dist = GridPoint::ManDistance(pos_a, finder[val], width);
		score -= maxdist - dist;
		val = data[pos_b];
		dist = GridPoint::ManDistance(pos_b, finder[val], width);
		score -= maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score -= tmp;
	}
	std::swap(data.at(pos_a), data.at(pos_b));
	{ // Add new score
		val = data[pos_a];
		dist = GridPoint::ManDistance(pos_a, finder[val], width);
		score += maxdist - dist;
		val = data[pos_b];
		dist = GridPoint::ManDistance(pos_b, finder[val], width);
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
	uint16_t    val;

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

score Heuristics::SuperSmartDistanceSwap(std::u16string& data, int width, int pos_a, int pos_b)
{
	std::vector<int>&   finder = State::solution_finder;
	score		score = 0;
	int			maxdist = width + width - 2;
	uint16_t    val;
	int			dist;
	int			tmp;

	{ // Substract old score
		val = data[pos_a];
		dist = GridPoint::ManDistance(pos_a, finder[val], width);
		score -= maxdist - dist;
		val = data[pos_b];
		dist = GridPoint::ManDistance(pos_b, finder[val], width);
		score -= maxdist - dist;
		val = 0;
		tmp = GridPoint::ManDistance(static_cast<int>(data.find(val)), finder[val], width);
		score -= tmp;
	}
		std::swap(data.at(pos_a), data.at(pos_b));
	{ // Add new score
		val = data[pos_a];
		dist = GridPoint::ManDistance(pos_a, finder[val], width);
		score += maxdist - dist;
		val = data[pos_b];
		dist = GridPoint::ManDistance(pos_b, finder[val], width);
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

	for (int counter = 0; counter < length; counter++)
	{
		int i = State::order[counter];
		uint16_t val = data[i];
		int indexSolution = State::solution_finder[val];//solution.find(val);
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
