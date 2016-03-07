//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#ifndef NPUZZLE_SOLVER_H
#define NPUZZLE_SOLVER_H

#include <string>
#include <list>
#include <set>
#include <unordered_set>
#include "State.hpp"

class Solver {
	public:
		class Result
		{
			public:
				int timeComplexity;
				int sizeComplexity;
				std::list<State::Movement>* movements;
				bool finished;
				Result(int timeComplexity, int sizeComplexity);
		};

		Solver(State* root);
		Result Step();
		~Solver();

	private:
		std::unordered_set<State*, State::hash_unordered_set, State::pred_unordered_set> opened;
		std::unordered_set<State*, State::hash_unordered_set, State::pred_unordered_set> closed;
		std::set<State*, State::comp_set> candidates;
};

#endif //NPUZZLE_SOLVER_H
