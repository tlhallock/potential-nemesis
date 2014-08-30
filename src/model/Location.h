/*
 * Location.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include "common.h"

#include <iostream>
#include <inttypes.h>

class Location {
public:
	Location(double x, double y);
	virtual ~Location();

	friend std::ostream& operator<<(std::ostream& os, const Location& r);
	sh_time_t get_time_to(const Location &l) const;

	bool is_same_location(const Location &other) const;

	double get_x() const;
	double get_y() const;
protected:
	virtual void append_to(std::ostream& os) const;
private:
	double x, y;
};

#endif /* LOCATION_H_ */
