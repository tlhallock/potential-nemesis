/*
 * Landfills.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Landfills.h"

#include "generate.h"

#include "common.h"

namespace
{
	std::vector<Location>* generate_landfills()
	{
		std::vector<Location> *ret = new std::vector<Location>;
		for (int i = 0; i < NUM_LANDFILLS; i++)
		{
			ret->push_back(generate_location());
		}
		return ret;
	}
}

Landfill::Landfill(double x, double y) :
	Location {x, y} {}

Landfill::~Landfill()   {}
