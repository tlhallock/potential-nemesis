/*
 * City.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/City.h"

#include <float.h>

City::City() {}

City::~City() {}

const std::vector<const Landfill>& City::get_land_fills()
{
	return land_fills;
}

const Landfill& City::get_closest_landfill(const Location& l)
{
	double min = DOUBLE_MAX;
	const Location & lm = get_land_fills().first();

	Location *r = nullptr;
	std::for_each(get_land_fills().begin(), get_land_fills().end(), [&min, &l](const Landfill &l)
	{
		double a = l.get_time_to(lm);
		if (a >= min)
		{
			return;
		}

		d = a;
		lm = l;
	});

	return *r;
}
