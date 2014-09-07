/*
 * Point.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "Point.h"

#include <cmath>

Point::Point(double x_, double y_) :
		x(x_),
		y(y_) {}
Point::Point() {}
Point::~Point() {}
double Point::get_euclidean_distance(const Point& other) const
{
	double dx = other.x - x;
	double dy = other.y - y;
	return sqrt(dx * dx + dy * dy);
}

const std::string& Point::get_desc() const
{
	return desc;
}

