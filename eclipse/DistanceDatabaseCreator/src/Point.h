/*
 * Point.h
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#ifndef POINT_H_
#define POINT_H_

#include <string>
#include <iostream>

class Point
{
public:
	Point();
	Point(double x, double y, const std::string &desc);
	~Point();

	double get_euclidean_distance(const Point &other) const;
	const std::string &get_desc() const;

	double get_x() const;
	double get_y() const;
	void set_x(double x);
	void set_y(double y);

	friend std::ostream& operator<<(std::ostream& out, const Point &p);
private:
	double x;
	double y;

	std::string desc;
};

Point get_random_point(const Point &lower, const Point &upper);

#endif /* POINT_H_ */
