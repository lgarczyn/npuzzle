//
// created by louis garczynski on 3/4/16.
//

#include "Heuristics.hpp"
#include "State.hpp"
#include <algorithm>

weighter	Heuristics::HeuristicFunction = Heuristics::ManhattanDistance;

score Heuristics::ManhattanDistance(const std::string& data, int width, int height)
{
	int					score = 0;
	int					length = State::size;
	std::vector<int>&	finder = State::solution_finder;
	uint16_t			val;

	(void)height;
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

static score	LinearConflictColumn(const std::string& data, int width, int height, int x, int y, int sy)
{
	score		score = 0;
	std::vector<int>&   finder = State::solution_finder;
	uint16_t	val2;
	int 		x2;
	int 		i2;

	for (int y2 = y + 1; y2 < height; ++y2)
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

static score	LinearConflictRow(const std::string& data, int width, int x, int y, int sx)
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

score Heuristics::LinearConflict(const std::string& data, int width, int height)
{
	score score = 0;
	uint16_t	val;
	std::vector<int>&   finder = State::solution_finder;
	int		sx;
	int		sy;
	int		i;

	for (int y = 0; y < height; ++y)
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
				score += LinearConflictColumn(data, width, height, x, y, sy);
		}
	}
	return (score + ManhattanDistance(data, width, height));
}

score Heuristics::SuperSmartDistance(const std::string& data, int width, int height)
{
	score				score = 0;
	uint16_t			val;
	int					length = State::size;
	const std::string&	solution = State::solution;

	(void)width;
	(void)height;
	for (int i = 0; i < length; i++)
	{
		val = data[i];
		if (data[i] != solution[i])
			score += 1;
	}
	return (score);
}
