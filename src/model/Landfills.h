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
	Landfill(const Location &loc, sh_time_t wait_time);
	~Landfill();

	sh_time_t get_wait_time() const;
private:
	sh_time_t wait_time;
};

#endif /* LANDFILLS_H_ */
