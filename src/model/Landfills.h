/*
 * Landfills.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef LANDFILLS_H_
#define LANDFILLS_H_

#include "model/Location.h"

#include <vector>

std::vector<Location> &get_land_fills();

Location get_closest_landfill(const Location &l);

#endif /* LANDFILLS_H_ */
