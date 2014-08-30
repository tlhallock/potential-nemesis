/*
 * NearestPointSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/NearestPointSolver.h"

#include "opt/OptimizerUtils.h"

#include <algorithm>

NearestPointSolver::NearestPointSolver(const Parameters &p) : ForDriverForStopSolver(p) {}
NearestPointSolver::~NearestPointSolver() {}

int NearestPointSolver::get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver)
{
	const Location& current_location = s->get_route(driver).get_current_location();
	std::sort(possibles.begin(), possibles.end(), [&originals, current_location](const int i1, const int i2)
	{
		sh_time_t t1 = current_location.get_time_to(originals.at(i1));
		sh_time_t t2 = current_location.get_time_to(originals.at(i2));
		return t1 > t2;
	});
	return possibles.at(random_decreasing_probability(possibles.size()));
}

std::string NearestPointSolver::get_name() const
{
	return "nearest";
}
