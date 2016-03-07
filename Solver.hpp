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
				std::list<State::Movement>* movements;
				bool finished;
				Result(int timeComplexity, int sizeComplexity);
		};

		Solver(State* root);
		Result step();
		~Solver();
		
		void	set_candidates(State* from);

	private:
		std::unordered_set<State*>	opened;
		std::unordered_set<State*>	closed;
		std::multiset<State*>			opened_set;
		std::vector<State*>			candidates;
};

