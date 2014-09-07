/*
 * DistanceSet.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "DistanceSet.h"

#include <algorithm>
#include <float.h>

#define TIME_PER_COORD 0

DistanceSet::DistanceSet() {}
DistanceSet::~DistanceSet() {}

const Point& DistanceSet::get_point(int index) const
{
	return points.at(index);
}

const double& DistanceSet::get_distance_between(int index1, int index2) const
{
	return distances[index1][index2];
}

int DistanceSet::get_closest_point(const Point& other) const
{
	int min_index = -1;
	double min_dist = DBL_MAX;

	int size = points.size();
	for (int i=0; i<size; i++)
	{
		double newd = other.get_euclidean_distance(points.at(i));
		if (newd < min_dist)
		{
			min_dist = newd;
			min_index = i;
		}
	}

	return min_index;
}


Guess DistanceSet::get_best_guess(const Point &p1, const Point &p2) const
{
	int idx1 = get_closest_point(p1);
	int idx2 = get_closest_point(p2);

	return Guess {
		get_point(idx1).get_euclidean_distance(p1) + get_point(idx2).get_euclidean_distance(p1),
		TIME_PER_COORD * (get_point(idx1).get_euclidean_distance(p1) + get_point(idx2).get_euclidean_distance(p1))
			+ get_distance_between(idx1, idx2)};
}
