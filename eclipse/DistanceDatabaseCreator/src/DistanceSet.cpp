/*
 * DistanceSet.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "DistanceSet.h"

#include "config.h"

#include <algorithm>
#include <float.h>
#include <fstream>
#include <iostream>

#define TIME_PER_COORD 0

DistanceSet::DistanceSet(const std::string &filename)
{
	std::ifstream in {filename};

	int num = -1;

	in >> num;

	if (num < 0 || num > 1000)
	{
		std::cout << "Invalid number of points in file " << filename << std::endl;
		return;
	}

	distances = make_array(num);
	durations = make_array(num);

	for (int i=0; i<num; i++)
	{
		int idx;
		double x, y;
		in >> idx;
		in >> x;
		in >> y;

		std::string str;
		getline(in, str);

		points.push_back(Point {x, y, str});
	}

	for (int i=0; i<num; i++)
	{
		for (int j=0; j<num; j++)
		{
			int idx1, idx2;
			int64_t duration, distance;

			in >> idx1;
			in >> idx2;
			in >> duration;
			in >> distance;

			if (idx1 < 0 || idx1 > 1000)
			{
				std::cout << "Invalid idx1 in file " << filename << std::endl;
				std::cout << idx1 << std::endl;
				points.clear();
				return;
			}

			if (idx2 < 0 || idx2 > 1000)
			{
				std::cout << "Invalid idx2 in file " << filename << std::endl;
				std::cout << idx2 << std::endl;
				points.clear();
				return;
			}

			if (distance < 0 || distance > 1000 * 1000) // less than 1000 km
			{
				std::cout << "Invalid distance in file " << filename << std::endl;
				std::cout << distance << std::endl;
				points.clear();
				return;
			}

			durations[idx1][idx2] = duration;
			distances[idx1][idx2] = distance;
		}
	}
}
DistanceSet::~DistanceSet()
{
	delete_array(distances, points.size());
	delete_array(durations, points.size());
}

const Point& DistanceSet::get_point(int index) const
{
	return points.at(index);
}

double DistanceSet::get_time_between(int index1, int index2) const
{
	return durations[index1][index2];
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

Guess DistanceSet::make_guess(int idx1, int idx2, const Point &p1, const Point &p2) const
{
	double c1 = get_point(idx1).get_euclidean_distance(p1);
	double c2 = get_point(idx2).get_euclidean_distance(p1);
	double cost = c1 + c2;
	return Guess { cost, TIME_PER_COORD * (c1 + c2) + get_time_between(idx1, idx2)};
}



Guess DistanceSet::get_best_guess(const Point &p1, const Point &p2) const
{
#if DONT_INCLUDE_ZERO_ANSWERS
	Guess g;

	int size = points.size();
	for (int idx1 = 0; idx1 < size; idx1++)
	{
		for (int idx2 = 0; idx2 < size; idx2++)
		{
			if (idx1 == idx2)
			{
				continue;
			}

			Guess another = make_guess(idx1, idx2, p1, p2);
			if (another.is_better_than(g))
			{
				g = another;
			}
		}
	}

	return g;
#else
	int idx1 = get_closest_point(p1);
	int idx2 = get_closest_point(p2);
	return make_guess(idx1, idx2, p1, p2);
#endif
}

double** DistanceSet::make_array(int dim)
{
	double **retval = (double **) malloc (dim * sizeof(*retval));
	for(int i=0; i<dim; i++)
	{
		retval[i] = (double *) malloc (dim * sizeof(*retval[i]));
	}
	return retval;
}

void DistanceSet::find_bounds(Point& lower, Point& upper) const
{
	lower.set_x(points.front().get_x());
	upper.set_x(points.front().get_x());
	lower.set_y(points.front().get_y());
	upper.set_y(points.front().get_y());

	auto end = points.end();
	for (auto it = points.begin(); it != end; ++it)
	{
		expand_bounds(lower, upper, *it);
	}
}

int DistanceSet::get_num_points() const
{
	return points.size();
}

void DistanceSet::delete_array(double **array, int dim)
{
	for (int i=0; i<dim; i++)
	{
		free(array[i]);
	}
	free(array);
}

void expand_bounds(Point& lower, Point& upper, const Point& another_point)
{
	if (another_point.get_x() < lower.get_x())
	{
		lower.set_x(another_point.get_x());
	}
	if (another_point.get_y() < lower.get_y())
	{
		lower.set_y(another_point.get_y());
	}
	if (another_point.get_x() > upper.get_x())
	{
		upper.set_x(another_point.get_x());
	}
	if (another_point.get_y() > upper.get_y())
	{
		upper.set_y(another_point.get_y());
	}
}

double DistanceSet::get_average_time_per_coord() const
{
	double sum = 0;
	int size = get_num_points();
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				continue;
			}

			double di = get_point(i).get_euclidean_distance(get_point(j));
			double time = durations[i][j];

			if (di == 0)
			{
				continue;
			}

			sum += time / di;
			count++;
		}
	}
	return sum / count;
}

double DistanceSet::get_average_time_per_meter() const
{
	double sum = 0;
	int size = get_num_points();
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (i == j)
			{
				continue;
			}

			double di = distances[i][j];
			double time = durations[i][j];

			if (di == 0)
			{
				continue;
			}

			sum += time / di;
			count++;
		}
	}
	return sum / count;
}
