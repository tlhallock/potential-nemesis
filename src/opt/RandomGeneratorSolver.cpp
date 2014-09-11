/*
 * RandomGeneratorSolver.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#include "opt/RandomGeneratorSolver.h"
#include "opt/Cost.h"

#include "model/Rules.h"

RandomGeneratorSolver::RandomGeneratorSolver(const Parameters &p) : ForDriverForStopSolver {p} {}
RandomGeneratorSolver::~RandomGeneratorSolver() {}

std::string RandomGeneratorSolver::get_name() const
{
	return "random";
}

bool RandomGeneratorSolver::get_next_request(
		const City &city,
		Solution *s,
		int driver)
{
	Route& output = s->get_route(driver);
	std::vector<action_ptr> *possibles = get_possibles(
			s,
			output.get_time_taken(),
			output.get_last_action(),
			city.get_all_actions());

	std::unique_ptr < std::vector<action_ptr> > dme { possibles };

	if (possibles->size() == 0)
	{
		return false;
	}

	return output.service_next(possibles->at(rand() % possibles->size()));
}
