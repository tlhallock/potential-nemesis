/*
 * Landfills.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Landfills.h"

#include "gen/generate.h"

std::vector<Location> &get_land_fills()
{
	static std::vector<Location> *landfills;
	if (landfills == nullptr)
	{
		landfills = generate_landfills();
	}
	return *landfills;
}

Location get_closest_landfill(const Location& l)
{
	double d = 10000;

	Location *r = nullptr;
	for (unsigned int i = 0; i < get_land_fills().size(); i++)
	{
		double a = l.get_time_to(get_land_fills().at(i));
		if (a >= d)
		{
			continue;
		}

		d = a;
		r = &get_land_fills().at(i);
	}

	return *r;
}