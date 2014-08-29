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
{
	// Assign each driver a landfill to spoke around...
	int index = 0;
	for (int i = 0; i < p.get_num_drivers(); i++)
	{
		locations.push_back(get_land_fills().at(index));
		index = (index + 1) % p.get_num_drivers();
	}
}

SpokeSolver::~SpokeSolver() {}

std::string SpokeSolver::get_name() const
{
	return "spoke";
}

int SpokeSolver::get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver)
{
	const Location& current_location = locations.at(driver);
	std::sort(possibles.begin(), possibles.end(), [&originals, current_location](const int i1, const int i2)
	{
		sh_time_t t1 = current_location.get_time_to(originals.at(i1));
		sh_time_t t2 = current_location.get_time_to(originals.at(i2));
		return t1 > t2;
	});
	return possibles.at(random_decreasing_probability(possibles.size()));
}
