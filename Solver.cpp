//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "Solver.hpp"

Solver::Solver(State* root) : _opened(1e6), _closed(1e6)
{
	State::initial_score = root->get_weight();
	_opened.insert(root);
	_opened_set.insert(root);
	_candidates = std::vector<State*>(4);
}

void	Solver::set_candidates(State* from)
{
	_candidates[0] = new State(from, State::Up);
	_candidates[1] = new State(from, State::Right);
	_candidates[2] = new State(from, State::Down);
	_candidates[3] = new State(from, State::Left);
}

Solver::Result Solver::step()
{
	Result result = Result(0, 0);

	if (!_opened.empty())
	{
		State* e = *_opened_set.begin();

		result.actual_state = e;
		if (e->is_final())
		{
			result.finished = true;
			result.movements = e->get_movements();
			//return (result);
		}
	//	else
		{
			_opened.erase(e);
			_opened_set.erase(_opened_set.begin());
			_closed.insert(e);
			set_candidates(e);
			for (auto s:_candidates)
			{
				auto openedEq = _opened.find(s);
				auto closedEq = _closed.find(s);
				bool isPreviousOpened = (openedEq != _opened.end());
				bool isPreviousClosed = (closedEq != _closed.end());
				if (!isPreviousClosed && !isPreviousOpened)
				{
					_opened.insert(s);
					_opened_set.insert(s);
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
							_opened.insert(previous);
							_opened_set.insert(previous);
							_closed.erase(previous);
						}
					}
					delete s;
				}
			}
		}
	}
	result.timeComplexity = _timeComplexity;
	result.sizeComplexity = _sizeComplexity;
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
