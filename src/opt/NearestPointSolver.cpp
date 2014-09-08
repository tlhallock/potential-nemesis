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

action_ptr NearestPointSolver::get_next_request(
		const City &city,
		const Solution *s,
		std::vector<action_ptr> *possibles,
		int driver)
{
	const Location& current_location = s->get_route(driver).get_current_location();
	std::sort(possibles->begin(), possibles->end(), [&current_location](const action_ptr &i1, const action_ptr &i2)
	{
		sh_time_t t1 = i1->get_time_to(current_location);
		sh_time_t t2 = i1->get_time_to(current_location);
		return t1 > t2;
	});
	return possibles->at(random_decreasing_probability(possibles->size()));
}

std::string NearestPointSolver::get_name() const
{
	return "nearest";
}
