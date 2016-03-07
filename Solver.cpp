//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "Solver.hpp"

Solver::Solver(State* root)
{
	opened.insert(root);
	opened_set.insert(root);
}

void	Solver::set_candidates(State* from)
{
	candidates.clear();
	candidates.push_back(new State(from, State::Up));
	candidates.push_back(new State(from, State::Right));
	candidates.push_back(new State(from, State::Down));
	candidates.push_back(new State(from, State::Left));
}

Solver::Result Solver::step()
{
	Result result = Result(0, 0);

	if (!opened.empty())
	{
		State* e = *opened_set.begin();

		if (e->is_final())
		{
			result.finished = true;
			result.movements = e->get_movements();
			return (result);
		}
		else
		{
			opened.erase(e);
			opened_set.erase(e);
			closed.insert(e);
			set_candidates(e);

			for (auto s:candidates)
			{
				if (opened.find(s) != opened.end()
						&&  closed.find(s) != closed.end())
				{
					opened.insert(s);
					opened_set.insert(s);
					s->set_distance(e->get_distance() + 1);
					s->set_parent(e->get_parent());
				}
				else
				{
					if (s->get_distance() > e->get_distance() + 1)
					{
						s->set_distance(e->get_distance() + 1);
						s->set_parent(e->get_parent());
						if (closed.find(s) == closed.end())
						{
							opened.insert(s);
							opened_set.insert(s);
							closed.erase(s);
						}
					}
				}
			}
		}
	}
	return (result);
}

Solver::~Solver() {}

Solver::Result::Result(int timeComplexity, int sizeComplexity):
	timeComplexity(timeComplexity),
	sizeComplexity(sizeComplexity),
	movements(nullptr),
	finished(false)
{}
