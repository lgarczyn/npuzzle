//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#pragma once

#include <string>
#include <list>
#include <set>
#include <unordered_set>
#include "State.hpp"
#define MAX_SOLUTION_LENGTH ((int)10000)
#define SOLVER_BUCKET_SIZE ((int)10000)

using set = std::unordered_set<State*, custom_hash, custom_equal_to>;

class Solver {
	public:

		class Result
		{
			public:
				int timeComplexity;
				int sizeComplexity;
				State*	actual_state;
				std::vector<State::Movement>* movements;
				bool finished;
				Result(int timeComplexity, int sizeComplexity);
		};

		Solver(State* root);
		Result step();
		set* get_opened_set(State* state);
		set* get_closed_set(State* state);
		State* get_smallest_state();
		~Solver();
		
		void	set_candidates(State* from);

	private:
		set* _opened[MAX_SOLUTION_LENGTH];
		set* _closed[MAX_SOLUTION_LENGTH];
		State* _candidates[4];
		int _timeComplexity;
		int _sizeComplexity;
		int _openCount;
};

