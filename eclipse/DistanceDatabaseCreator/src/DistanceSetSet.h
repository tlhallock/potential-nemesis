/*
 * DistanceSetSet.h
 *
 *  Created on: Sep 8, 2014
 *      Author: thallock
 */

#ifndef DISTANCESETSET_H_
#define DISTANCESETSET_H_

#include "DistanceSet.h"

class DistanceSetSet
{
public:
	DistanceSetSet(const std::string &filename);
	virtual ~DistanceSetSet();

	void find_bounds(Point &lower, Point &upper) const;
	Guess get_best_guess(const Point &p1, const Point &p2) const;
	double get_average_cost(int num_iters) const;

	int get_num_points() const;

	double get_average_time_per_coord() const;
	double get_average_time_per_meter() const;
private:
	std::vector<const DistanceSet *> sets;
};

#endif /* DISTANCESETSET_H_ */
