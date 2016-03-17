//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include <set>
#include "Solver.hpp"
#include "tools.h"

Solver::Solver(State* root) : _opened(1e6), _closed(1e6)
{
	State::initial_score = root->get_weight();
	_opened.insert(root);
	_opened_set.insert(root);
	_candidates = std::vector<State*>(4);
	_sizeComplexity = 0;
	_timeComplexity = 0;
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

void super_erase(std::multiset<State*, custom_less>& set, State* s)
{
	auto pit = set.equal_range(s);
	auto it = pit.first;
	auto ite = pit.second;
	custom_equal_to	cmp;

	while (it != ite) {
		if (cmp(*it, s)) {
			set.erase(it);
			return;
		}
		++it;
	}
	throw std::logic_error("could not find state in multi set");
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
				if (s) {

					auto openedEq = _opened.find(s);
					auto closedEq = _closed.find(s);
					bool isPreviousOpened = (openedEq != _opened.end());
					bool isPreviousClosed = (closedEq != _closed.end());
					custom_less			less;

					if (isPreviousClosed || isPreviousOpened)
					{
						auto previous = isPreviousOpened ? *openedEq : *closedEq;

						if (less(s, previous))
						{
							if (isPreviousClosed)
							{
								_closed.erase(closedEq);
							}
							else if (isPreviousOpened)
							{
								_opened.erase(openedEq);
								super_erase(_opened_set, previous);
							}
							delete previous;
							_opened.insert(s);
							_opened_set.insert(s);
						}
						else
							delete s;
					}
					else if (!isPreviousClosed && !isPreviousOpened)
					{
						_opened.insert(s);
						_opened_set.insert(s);
						_timeComplexity++;
					}
					int openedSize = _opened.size();
					if (openedSize > _sizeComplexity)
						_sizeComplexity = openedSize;
				}
			}
		}
	}
	result.sizeComplexity = _sizeComplexity;
	result.timeComplexity = _timeComplexity;
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
