/*
 * ForDriverForStopSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/ForDriverForStopSolver.h"

ForDriverForStopSolver::ForDriverForStopSolver(const Parameters &p) : Solver{p} {}

ForDriverForStopSolver::~ForDriverForStopSolver() {}

Solution* ForDriverForStopSolver::solve(const std::vector<Request>& original_requests)
{
	int size = original_requests.size();

	bool *already_serviced = (bool *) malloc(size);
	for (int i = 0; i < size; i++)
	{
		already_serviced[i] = 0;
	}

	int num_drivers = p.get_num_drivers();
	Solution *s = new Solution { num_drivers };
	while (true)
	{
		bool could_add = false;

		for (int i = 0; i < num_drivers; i++)
		{
			Route &output = s->get_route(i);

			std::vector<int> possibles;
			for (unsigned int i = 0; i < original_requests.size(); i++)
			{
				const Action& a = original_requests.at(i);
				if (output.can_service_next(a) && !already_serviced[i])
				{
					possibles.push_back(i);
				}
			}
			int idx;
			if (possibles.size() != 0
					&& (idx = get_next_request(original_requests, possibles, s, i)) >= 0)
			{
				could_add = true;
				already_serviced[idx] = true;
				output.service_next(new Request { original_requests.at(idx) });

				continue;
			}

			std::vector<Action> more = output.get_next_possibles();
			if (more.size() == 0)
			{
				continue;
			}

			output.service_next(new Action { more.at(rand() % more.size()) });
			could_add = true;
		}

		if (!could_add)
		{
			break;
		}
	}

	free(already_serviced);

	return s;
}
