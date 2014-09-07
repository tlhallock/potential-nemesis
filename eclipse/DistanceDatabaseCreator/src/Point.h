/*
 * Point.h
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#ifndef POINT_H_
#define POINT_H_

#include <string>

class Point
{
public:
	Point();
	Point(double x, double y);
	~Point();

	double get_euclidean_distance(const Point &other) const;
	const std::string &get_desc() const;
private:
	double x;
	double y;

	std::string desc;
};

#endif /* POINT_H_ */
