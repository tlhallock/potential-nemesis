/*
 * RandomGeneratorSolver.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#include "opt/RandomGeneratorSolver.h"
#include "opt/Cost.h"

RandomGeneratorSolver::RandomGeneratorSolver(const Parameters &p) : ForDriverForStopSolver {p} {}
RandomGeneratorSolver::~RandomGeneratorSolver() {}

std::string RandomGeneratorSolver::get_name() const
{
	return "random";
}

action_ptr RandomGeneratorSolver::get_next_request(
		const City &city,
		const Solution *s,
		std::vector<action_ptr> *possibles,
		int driver)
{
	return possibles->at(rand() % possibles->size());
}
