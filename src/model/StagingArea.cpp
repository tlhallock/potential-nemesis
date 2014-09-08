/*
 * StagingArea.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/StagingArea.h"

StagingArea::StagingArea(const Location &loc, sh_time_t wait_time_, int max_containers_) :
	Location{loc},
	wait_time (wait_time_),
	max_containers(max_containers_) {}

StagingArea::~StagingArea() {}

