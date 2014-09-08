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
	return get_close(s->get_route(driver).get_current_location(), possibles);
}

std::string NearestPointSolver::get_name() const
{
	return "nearest";
}
