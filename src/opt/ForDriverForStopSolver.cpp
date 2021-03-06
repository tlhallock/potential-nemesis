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

	Solution s { &city };

	bool could_add = true;
	while (could_add)
	{
		could_add = false;
		for (int i = 0; i < num_drivers; i++)
		{
			could_add |= get_next_request(city, &s, i);
		}
	}

	return s;
}

