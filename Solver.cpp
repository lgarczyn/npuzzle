//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "Solver.hpp"

Solver::Solver(State* root)
{
	opened.insert(root);
	candidates.insert(root);
};

Solver::Result Solver::Step()
{
	Result result = Result(0, 0);

	if (!opened.empty())
	{
		State* e = *candidates.begin();
		if (e->is_final())
		{
			result.finished = true;
			result.movements = e->get_movements();
			return (result);
		}
		else
		{
			opened.erase(e);
			candidates.erase(e);
			closed.insert(e);
			//FOREACH POSSIBILITY S FROM E
			{
				State* s;

				auto openedFound = opened.find(s);
				auto closedFound = closed.find(s);

				if (openedFound == opened.end() && closedFound == closed.end())
				{
					opened.insert(s);
				}
				else
				{
					if (s->get_distance() < ()->get_distance())
					{
						opened->
					}
				}
			}
		}
	}
}

Solver::~Solver();

Solver::Result::Result(int timeComplexity, int sizeComplexity):
	timeComplexity(timeComplexity),
	sizeComplexity(sizeComplexity),
	movements(nullptr),
	finished(false)
{};
