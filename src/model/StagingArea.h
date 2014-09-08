/*
 * StagingArea.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef STAGINGAREA_H_
#define STAGINGAREA_H_

#include "model/Location.h"

class StagingArea : public Location
{
public:
	StagingArea(const Location &loc,
			sh_time_t wait_time,
			int max_containers);
	virtual ~StagingArea();
private:
	sh_time_t wait_time;
	int max_containers;
};

#endif /* STAGINGAREA_H_ */
