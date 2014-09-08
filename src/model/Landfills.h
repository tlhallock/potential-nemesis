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
public:
	Landfill(const Location &loc);
	~Landfill();
};

#endif /* LANDFILLS_H_ */
