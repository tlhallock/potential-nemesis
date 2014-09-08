/*
 * Point.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "Point.h"

#include <cmath>
#include <stdlib.h>

Point::Point(double x_, double y_, const std::string &desc_) :
		x(x_),
		y(y_),
		desc(desc_) {}
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

double Point::get_x() const
{
	return x;
}

double Point::get_y() const
{
	return y;
}

void Point::set_x(double x)
{
	this->x = x;
}

void Point::set_y(double y)
{
	this->y = y;
}

Point get_random_point(const Point& lower, const Point& upper)
{
	double x = lower.get_x() + (upper.get_x() - lower.get_x()) * rand() / (double) RAND_MAX;
	double y = lower.get_y() + (upper.get_y() - lower.get_y()) * rand() / (double) RAND_MAX;
	return Point {x, y, "random point"};
}


std::ostream& operator<<(std::ostream& out, const Point &p)
{
	out << p.x << ", " << p.y << " '" << p.desc << "'" << std::endl;
	return out;
}
