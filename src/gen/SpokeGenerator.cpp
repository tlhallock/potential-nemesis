/*
 * SpokeGenerator.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include <gen/SpokeGenerator.h>

SpokeGenerator::SpokeGenerator() {}
SpokeGenerator::~SpokeGenerator() {}

Solution SpokeGenerator::generate(const std::vector<Request>& original_requests, const Parameters& params)
{
	return Solution {params.get_num_drivers()};
}
