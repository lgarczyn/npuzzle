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

static score	LinearConflictColumn(const std::u16string& data, int width, int x, int y, int sy)
{
	score		score = 0;
	std::vector<int>&   finder = State::solution_finder;
	uint16_t	val2;
	int 		x2;
	int 		i2;

	for (int y2 = y + 1; y2 < width; ++y2)
	{
		val2 = data[y2 * width + x];
		i2 = finder[val2];
		x2 = i2 % width;
		if (x == x2)
		{
			if ((i2 / width) < sy)
			{
				score += 2;
			}
		}
	}
	return (score);
}

static score	LinearConflictRow(const std::u16string& data, int width, int x, int y, int sx)
{
	score		score = 0;
	std::vector<int>&   finder = State::solution_finder;
	uint16_t	val2;
	int 		y2;
	int 		i2;

	for (int x2 = x + 1; x2 < width; ++x2)
	{
		val2 = data[y * width + x2];
		i2 = finder[val2];
		y2 = i2 / width;
		if (y == y2)
		{
			if ((i2 % width) < sx)
			{
				score += 2;
			}
		}
	}
	return (score);
}

score Heuristics::LinearConflict(const std::u16string& data, int width)
{
	score score = 0;
	uint16_t	val;
	std::vector<int>&   finder = State::solution_finder;
	int		sx;
	int		sy;
	int		i;

	for (int y = 0; y < width; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			val = data[y * width + x];
			i = finder[val];
			sx = (i % width);
			sy = (i / width);
			if (y == finder[val] / width)
				score += LinearConflictRow(data, width, x, y, sx);
			if (x == finder[val] % width)
				score += LinearConflictColumn(data, width, x, y, sy);
		}
	}
	return (score + ManhattanDistance(data, width));
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
	score		score = 0;
	uint16_t	val;
	int			length = data.length();
	const std::u16string&	solution = State::solution;

	for (int i = 0; i < length; i++)
	{
		val = data[i];
		if (data[i] != solution[i])
			score += 1;
	}
	return (score);
}
