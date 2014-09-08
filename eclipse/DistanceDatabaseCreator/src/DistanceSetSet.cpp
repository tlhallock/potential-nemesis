/*
 * DistanceSetSet.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: thallock
 */

#include "DistanceSetSet.h"

#include <fstream>
#include <iostream>

DistanceSetSet::DistanceSetSet(const std::string &filename)
{
	std::string line;
	std::ifstream in {filename};

	while (getline(in, line))
	{
		auto s = new DistanceSet{line};
		if (s->get_num_points() <= 1)
		{
			delete s;
			continue;
		}
		sets.push_back(s);
	}
}

DistanceSetSet::~DistanceSetSet()
{
	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		delete *it;
	}
}

Guess DistanceSetSet::get_best_guess(const Point &p1, const Point &p2) const
{
	Guess g;

	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		Guess another = (*it)->get_best_guess(p1, p2);
		if (another.is_better_than(g))
		{
			g = another;
		}
	}

	return g;
}

double DistanceSetSet::get_average_cost(int num_iters) const
{
	double sum = 0;

	Point upper;
	Point lower;
	find_bounds(lower, upper);

	for (int i = 0; i < num_iters; i++)
	{
		Point p1 = get_random_point(lower, upper);
		Point p2 = get_random_point(lower, upper);

		sum += get_best_guess(p1, p2).get_cost();
	}

	return sum / num_iters;
}

double DistanceSetSet::get_average_time(int num_iters) const
{
	double sum = 0;

	Point upper;
	Point lower;
	find_bounds(lower, upper);

	for (int i = 0; i < num_iters; i++)
	{
		Point p1 = get_random_point(lower, upper);
		Point p2 = get_random_point(lower, upper);

		sum += get_best_guess(p1, p2).get_answer();
	}

	return sum / num_iters;
}

void DistanceSetSet::find_bounds(Point& lower, Point& upper) const
{
	sets.front()->find_bounds(lower, upper);

	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		Point nlower;
		Point nupper;
		(*it)->find_bounds(nlower, nupper);

		expand_bounds(lower, upper, nlower);
		expand_bounds(lower, upper, nupper);
	}
}

int DistanceSetSet::get_num_points() const
{
	int sum = 0;
	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		sum += (*it)->get_num_points();
	}
	return sum;
}

double DistanceSetSet::get_average_time_per_coord() const
{
	double sum = 0;
	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		sum += (*it)->get_average_time_per_coord();
	}
	return sum / sets.size();
}

double DistanceSetSet::get_average_time_per_meter() const
{
	double sum = 0;
	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		sum += (*it)->get_average_time_per_meter();
	}
	return sum / sets.size();
}
