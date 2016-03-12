//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include "Solver.hpp"
#include "tools.h"

Solver::Solver(State* root) : _opened(1e6), _closed(1e6)
{
	State::initial_score = root->get_weight();
	_opened.insert(root);
	_opened_set.insert(root);
	_candidates = std::vector<State*>(4);
}

void	Solver::set_candidates(State* from)
{
	const std::u16string&	data = from->get_data();
	int		w = State::width;
	int		h = State::height;
	int		pos = data.find(static_cast<char16_t>(0));
	State::Movement	prev_move = from->get_movement();

	std::fill(_candidates.begin(), _candidates.end(), nullptr);
	if (pos - w >= 0 && prev_move != State::Down)
		_candidates[0] = new State(from, State::Up);
	if ((pos + 1) % w > 0 && prev_move != State::Left)
		_candidates[1] = new State(from, State::Right);
	if (pos + w < (w * h) && prev_move != State::Up)
		_candidates[2] = new State(from, State::Down);
	if (pos % w > 0 && prev_move != State::Right)
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
		}
		else
		{
			_opened.erase(e);
			_opened_set.erase(_opened_set.begin());
			_closed.insert(e);
			set_candidates(e);
			for (auto s:_candidates)
			{
				if (s)
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
						auto previous = isPreviousOpened ? *openedEq : *closedEq;
						custom_less less;
						if (less(s, previous))
						{
							if (!isPreviousOpened)
							{
								_opened.erase(openedEq);
								_opened_set.erase(previous);
							}
							else
							{
								_closed.erase(closedEq);
							}
							_opened.insert(s);
							_opened_set.insert(s);
							//delete previous;
						}
						else
						{
							delete s;
						}
					}
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
