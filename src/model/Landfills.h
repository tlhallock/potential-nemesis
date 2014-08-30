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

class Landfill : public Location
{
	Landfill(double x, double y);
	~Landfill();
};

#endif /* LANDFILLS_H_ */
