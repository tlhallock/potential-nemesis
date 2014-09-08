/*
 * Constraints.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Parameters.h"

Parameters::Parameters() {}

Parameters::~Parameters() {}

int Parameters::get_num_drivers() const { return 3; }

int Parameters::get_num_requests() const
{
	return get_num_drivers() * 10;
}

int Parameters::num_random_requests() const
{
	return 70;
}

int Parameters::num_random_land_fills() const
{
	return 5;
}
