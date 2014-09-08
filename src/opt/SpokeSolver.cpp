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
	return get_close(*get_location(city, driver), possibles);
}

const Landfill *SpokeSolver::get_location(const City& city, int idx)
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
	return locations.at(idx);
}
