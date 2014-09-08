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

Solution* ForDriverForStopSolver::solve(const City &city)
{
	int num_drivers = p.get_num_drivers();
	Solution *s = new Solution { num_drivers };
	while (true)
	{
		bool could_add = false;

		for (int i = 0; i < num_drivers; i++)
		{
			Route &output = s->get_route(i);

			action_ptr a {nullptr};
			{
				std::vector<action_ptr> *possibles = get_possibles(
						s,
						output.get_time_taken(),
						output.get_last_action(),
						city.get_all_actions());
				std::unique_ptr < std::vector<action_ptr> > dme { possibles };

				if (possibles->size() == 0)
				{
					continue;
				}

				a = get_next_request(city, s, possibles, i);
			}

			if (a == nullptr)
			{
				continue;
			}

			could_add = true;
			output.service_next(a);
		}

		if (!could_add)
		{
			break;
		}
	}

	return s;
}
