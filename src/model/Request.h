/*
 * Request.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "model/Action.h"
#include "model/Location.h"

#include "common.h"

#include <string>
#include <inttypes.h>
#include <iostream>

class Request : public Action
{
public:
	Request(Location l, Operation a, sh_time_t start_time, sh_time_t stop_time);
	virtual ~Request();

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;

	virtual sh_time_t get_minimum_time() const;
	virtual sh_time_t get_maximum_time() const;

	int get_points() const;
protected:
	virtual void append_to(std::ostream& os) const;

private:
	sh_time_t start_time;
	sh_time_t stop_time;
};

#endif /* REQUEST_H_ */
