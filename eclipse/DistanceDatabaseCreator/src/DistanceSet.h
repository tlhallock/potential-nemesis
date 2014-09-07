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
	DistanceSet();
	virtual ~DistanceSet();

	const Point &get_point(int index) const;
	const double &get_distance_between(int index1, int index2) const;
	int get_closest_point(const Point &other) const;

	Guess get_best_guess(const Point &p1, const Point &p2) const;
private:
	std::vector<const Point> points;
	double **distances;
};

#endif /* DISTANCESET_H_ */
