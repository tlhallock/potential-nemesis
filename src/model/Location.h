/*
 * Location.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include "common.h"

#include "XmlObject.h"

#include <iostream>
#include <inttypes.h>

class Location {
public:
	Location();
	Location(double x, double y);
	Location(const Location &loc);
	virtual ~Location();

	sh_time_t get_time_to(const Location &l) const;

	bool is_same_location(const Location &other) const;

	double get_x() const;
	double get_y() const;

	friend std::ostream& operator<<(std::ostream& os, const Location& r);
	virtual void loadXml(const tinyxml2::XMLElement* element);
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* element) const;

	bool operator==(const Location &other) const;
	bool operator<(const Location &other) const;
private:
	double x, y;
};

#endif /* LOCATION_H_ */
