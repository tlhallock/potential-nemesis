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

int RandomGeneratorSolver::get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver)
{
	return possibles.at(rand() % possibles.size());
}
