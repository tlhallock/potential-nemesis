/*
 * DistanceSet.h
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#ifndef DISTANCESET_H_
#define DISTANCESET_H_

#include "Point.h"
#include "Guess.h"

#include <vector>

class DistanceSet
{
public:
	DistanceSet(const std::string &filename);
	virtual ~DistanceSet();

	const Point &get_point(int index) const;
	double get_time_between(int index1, int index2) const;
	int get_closest_point(const Point &other) const;

	Guess get_best_guess(const Point &p1, const Point &p2) const;

	void find_bounds(Point &lower, Point &upper) const;

	double get_average_time_per_coord() const;
	double get_average_time_per_meter() const;

	int get_num_points() const;
private:
	double **make_array(int dim);
	void delete_array(double **array, int dim);
	Guess make_guess(int idx1, int idx2, const Point &p1, const Point &p2) const;

	std::vector<Point> points;
	double **distances;
	double **durations;
};

void expand_bounds(Point &lower, Point &upper, const Point &another_point);

#endif /* DISTANCESET_H_ */
