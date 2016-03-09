//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "Solver.hpp"

Solver::Solver(State* root) : opened(1e6), closed(1e6)
{
	State::initial_score = root->get_weight();
	opened.insert(root);
	opened_set.insert(root);
	candidates = std::vector<State*>(4);
}

void	Solver::set_candidates(State* from)
{
	candidates[0] = new State(from, State::Up);
	candidates[1] = new State(from, State::Right);
	candidates[2] = new State(from, State::Down);
	candidates[3] = new State(from, State::Left);
}

Solver::Result Solver::step()
{
	Result result = Result(0, 0);

	if (!opened.empty())
	{
		State* e = *opened_set.begin();

		result.actual_state = e;
		if (e->is_final())
		{
			result.finished = true;
			result.movements = e->get_movements();
			//return (result);
		}
	//	else
		{
			opened.erase(e);
			opened_set.erase(opened_set.begin());
			closed.insert(e);
			set_candidates(e);
			for (auto s:candidates)
			{
				auto openedEq = opened.find(s);
				auto closedEq = closed.find(s);
				bool isPreviousOpened = (openedEq != opened.end());
				bool isPreviousClosed = (closedEq != closed.end());
				if (!isPreviousClosed && !isPreviousOpened)
				{
					opened.insert(s);
					opened_set.insert(s);
				}
				else
				{
					State *previous = isPreviousOpened ? *openedEq : *closedEq;

					if (s->get_distance() < previous->get_distance())
					{
						previous->set_distance(s->get_distance());
						previous->set_parent(s->get_parent());
						if (!isPreviousOpened)
						{
							opened.insert(previous);
							opened_set.insert(previous);
							closed.erase(previous);
						}
					}
					delete s;
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
	actual_state(nullptr),
	movements(nullptr),
	finished(false)
{
}
