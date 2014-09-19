/*
 * StagingArea.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/StagingArea.h"

StagingArea::StagingArea() : Location {0,0}, wait_time{0}, max_containers{INT_MAX} {}

StagingArea::StagingArea(const Location &loc, sh_time_t wait_time_, int max_containers_) :
	Location{loc},
	wait_time (wait_time_),
	max_containers(max_containers_) {}

StagingArea::~StagingArea() {}

std::ostream& operator<<(std::ostream& os, const StagingArea& r)
{
	return os << Location {r} << " wait time = " << r.wait_time << ", max containers = " << r.max_containers;
}
