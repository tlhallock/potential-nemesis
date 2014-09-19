/*
 * ForDriverForStopSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/ForDriverForStopSolver.h"

#include "model/Rules.h"

ForDriverForStopSolver::ForDriverForStopSolver(const Parameters &p) : Solver{p} {}
ForDriverForStopSolver::~ForDriverForStopSolver() {}

Solution ForDriverForStopSolver::solve(const City &city)
{
	int num_drivers = p.get_num_drivers();

	Solution *s = new Solution { &city };
	while (true)
	{
		bool could_add = false;

		for (int i = 0; i < num_drivers; i++)
		{
			could_add |= get_next_request(city, s, i);
#if 0
std::vector<action_ptr> *possibles = get_possibles(
		s,
		output.get_time_taken(),
		output.get_last_action(),
		city.get_all_actions());
std::unique_ptr < std::vector<action_ptr> > dme { possibles };
if (possibles->size() == 0)
{
	return action_ptr {nullptr};
}
#endif
		}

		if (!could_add)
		{
			break;
		}
	}

	std::unique_ptr<Solution> dme {s};

	return *s;
}

