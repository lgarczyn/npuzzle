//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#include <set>
#include "Solver.hpp"
#include "tools.h"


set*	Solver::get_opened_set(State *state)
{
	int index = State::get_index(state);

	if (index >= MAX_SOLUTION_LENGTH)
		throw std::logic_error("State index too big: check get_index function.");

	if (_opened[index] == nullptr)
		_opened[index] = new std::unordered_set<State*, custom_hash, custom_equal_to>(SOLVER_BUCKET_SIZE);
	return _opened[index];
}

State*	Solver::get_smallest_state()
{
	for (int i = 0; i < MAX_SOLUTION_LENGTH; i++)
	{
		if (_opened[i] && !_opened[i]->empty())
		{
			return (*_opened[i]->begin());
		}
	}
	throw new std::logic_error("No valid opened state but count is still superior to 0");
}

Solver::Solver(State* root) : _opened()
{

	State::initial_score = root->get_weight();
	get_opened_set(root)->insert(root);
	_openCount = 1;
	_sizeComplexity = 0;
	_timeComplexity = 0;
	_stepCount = 0;
}

void	Solver::set_candidates(State* from)
{
	const std::string&	data = from->get_data();
	int		w = State::width;
	int		l = State::size;
	int		pos = data.find(static_cast<char16_t>(0));
	State::Movement	prev_move = from->get_movement();

	if (pos - w >= 0 && prev_move != State::Down)
		_candidates[0] = new State(from, State::Up);
	else
		_candidates[0] = nullptr;

	if ((pos + 1) % w > 0 && prev_move != State::Left)
		_candidates[1] = new State(from, State::Right);
	else
		_candidates[1] = nullptr;

	if (pos + w < l && prev_move != State::Up)
		_candidates[2] = new State(from, State::Down);
	else
		_candidates[2] = nullptr;

	if (pos % w > 0 && prev_move != State::Right)
		_candidates[3] = new State(from, State::Left);
	else
		_candidates[3] = nullptr;
}

Solver::Result Solver::step()
{
	Result result = Result(0, 0);

	_stepCount++;
	if (_openCount > 0)
	{
		State* e = get_smallest_state();

		result.actual_state = e;
		if (e->is_final())
		{
			result.finished = true;
			result.movements = e->get_movements();
		}
		else
		{
			get_opened_set(e)->erase(e);
			_openCount--;

			set_candidates(e);
			for (int i = 0; i < 4; i++)
			{
				auto s = _candidates[i];
				if (s) {
					get_opened_set(s)->insert(s);
					_openCount++;
					_timeComplexity++;
					if (_openCount > _sizeComplexity)
						_sizeComplexity = _openCount;
				}
			}
		}
	}
	if (_stepCount % CLEANUP_INTERVAL == 0)
		cleanup_duplicates();

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

void Solver::cleanup_duplicates()
{
	set library;

	int counter = 0;

	for (auto set:_opened)
	{
		if (set)
		{
			auto it = set->begin();
			while (it != set->end())
			{
				if (library.find(*it) != library.end())
				{
					it = set->erase(it);
				}
				else
				{
					library.insert(*it);
					it++;
				}
			}

			if (++counter > CLEANUP_DEPTH)
				return;;
		}
	}
}
