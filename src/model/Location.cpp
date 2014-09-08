/*
 * Location.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Location.h"

#include <cmath>
#include <iomanip>

Location::Location(double x_, double y_) : x{x_}, y{y_} {}
Location::Location(const Location& loc) :
		Location{loc.get_x(), loc.get_y()} {}
Location::~Location() {}

std::ostream& operator<<(std::ostream& os, const Location& r)
{
	os << "{" << std::setw(10) << r.x << " , " << std::setw(10) << r.y << " }";
	r.append_to(os);
	return os;
}

sh_time_t Location::get_time_to(const Location& l) const
{
	double xd = l.x - x;
	double yd = l.y - y;

	return (int64_t) sqrt(xd * xd + yd * yd);
}

void Location::append_to(std::ostream& os) const {}

bool Location::is_same_location(const Location& other) const
{
	return x == other.x && y == other.y;
}

double Location::get_x() const
{
	return x;
}

double Location::get_y() const
{
	return y;
}

