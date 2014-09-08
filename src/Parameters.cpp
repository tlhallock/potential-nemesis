/*
 * Constraints.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Parameters.h"

Parameters::Parameters() {}
Parameters::~Parameters() {}

int Parameters::get_num_drivers() const
{
	return 1;
}

int Parameters::num_random_requests() const
{
	return 70;
}

int Parameters::num_random_land_fills() const
{
	return 5;
}

int Parameters::num_random_staging_areas() const
{
	return 3;
}

double Parameters::get_scale() const
{
	return 100;
}
