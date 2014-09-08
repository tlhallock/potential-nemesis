/*
 * Landfills.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Landfills.h"

#include "generate.h"

#include "common.h"


Landfill::Landfill(const Location &loc, sh_time_t wait_time_) :
	Location {loc},
	wait_time(wait_time_) {}

Landfill::~Landfill() {}

sh_time_t Landfill::get_wait_time() const
{
	return wait_time;
}
