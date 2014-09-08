/*
 * SpokeSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/SpokeSolver.h"

#include "model/Landfills.h"
#include "OptimizerUtils.h"

SpokeSolver::SpokeSolver(const Parameters &p) :
	ForDriverForStopSolver {p}
{}

SpokeSolver::~SpokeSolver() {}

std::string SpokeSolver::get_name() const
{
	return "spoke";
}

action_ptr SpokeSolver::get_next_request(
		const City &city,
		const Solution *s,
		std::vector<action_ptr> *possibles,
		int driver)
{
	const Location *current_location = get_location(city, driver);
	std::sort(possibles->begin(), possibles->end(), [current_location](const action_ptr &i1, const action_ptr &i2)
	{
		sh_time_t t1 = i1->get_time_to(*current_location);
		sh_time_t t2 = i2->get_time_to(*current_location);
		return t1 > t2;
	});
	return possibles->at(random_decreasing_probability(possibles->size()));
}

const Landfill *SpokeSolver::get_location(const City& city, int i)
{
	if (locations.size() == 0)
	{
		// Assign each driver a landfill to spoke around...
		int index = 0;
		for (int i = 0; i < p.get_num_drivers(); i++)
		{
			locations.push_back(&city.get_land_fill(index));
			index = (index + 1) % city.get_num_land_fills();
		}
	}
	return locations.at(i);
}
