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

	std::vector<const Action*> *possibles = get_possibles(
			s,
			output.get_time_to_end(),
			output.get_last_action(),
			city);

	std::unique_ptr < std::vector<const Action*> > dme { possibles };

	if (possibles->size() == 0)
	{
		return false;
	}

	return s->service_next(driver, possibles->at(rand() % possibles->size()));
}
