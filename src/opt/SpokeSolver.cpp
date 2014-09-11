/*
 * SpokeSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/SpokeSolver.h"

#include "model/Rules.h"

#include "model/Landfills.h"
#include "OptimizerUtils.h"

SpokeSolver::SpokeSolver(const Parameters &p) :
	NearestPointSolver {p} {}

SpokeSolver::~SpokeSolver() {}

std::string SpokeSolver::get_name() const
{
	return "spoke";
}

const operation_location_constraint& SpokeSolver::get_constraints(const City &city, int driver)
{
	if (constraints.size() == 0)
	{
		// Assign each driver a landfill to spoke around...
		int index = 0;
		for (int i = 0; i < p.get_num_drivers(); i++)
		{
			std::map<const Operation, const Location> c;
			c.insert(std::pair<const Operation, const Location> {Dump, city.get_land_fill(index)});
			constraints.push_back(c);
			index = (index + 1) % city.get_num_land_fills();
		}
	}
	return constraints.at(driver);
}
