/*
 * SpokeSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/SpokeSolver.h"

#include "model/Rules.h"

#include "OptimizerUtils.h"

#include <set>

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
		std::set<location> land_fills;
		int num_actions = city.get_num_stops();
		for (int i = 0; i < num_actions; i++)
		{
			if (city.get_stop(i)->get_operation() != Dump)
			{
				continue;

			}
			land_fills.insert(city.get_stop(i)->get_location());
		}

		auto it = land_fills.begin();


		// Assign each driver a landfill to spoke around...
		for (int i = 0; i < p.get_num_drivers(); i++)
		{
			if (it == land_fills.end())
			{
				it = land_fills.begin();
			}
			location l = *it;
			std::map<const Operation, const location> c;
			c.insert(std::pair<const Operation, const location> {Dump, l});
			constraints.push_back(c);

			it++;
		}
	}
	return constraints.at(driver);
}
