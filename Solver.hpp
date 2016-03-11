//
// Created by Louis GARCZYNSKI on 3/4/16.
//

#pragma once

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
				State*	actual_state;
				std::vector<State::Movement>* movements;
				bool finished;
				Result(int timeComplexity, int sizeComplexity);
		};

		Solver(State* root);
		Result step();
		~Solver();
		
		void	set_candidates(State* from);

	private:
		std::unordered_set<State*> _opened;
		std::unordered_set<State*> _closed;
		std::multiset<State*> _opened_set;
		std::vector<State*> _candidates;
		int _timeComplexity;
		int _sizeComplexity;
};

