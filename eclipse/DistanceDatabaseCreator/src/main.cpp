/*
 * main.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "DistanceSet.h"

#include <iostream>

#include <float.h>

Guess get_best_guess(const std::vector<const DistanceSet> &sets, const Point &p1, const Point &p2)
{
	int size = sets.size();

	Guess g;

	auto end = sets.end();
	for (auto it = sets.begin(); it != end; ++it)
	{
		Guess another = it->get_best_guess(p1, p2);
		if (another.is_better_than(g))
		{
			g = another;
		}
	}
	return g;
}

double get_estimated_cost(std::vector<const DistanceSet> &sets)
{
	int num_iters = 100;

	double sum = 0;

	for (int i = 0; i < num_iters; i++)
	{
		Point p1;
		Point p2;
		sum += get_best_guess(sets, p1, p2).get_cost();
	}

	return sum / num_iters;
}


int main(int argc, char **argv)
{
	// Load all distance sets
	std::vector<const DistanceSet> sets;

	Point p1;
	Point p2;


	std::cout << get_estimated_cost(sets) << std::endl;
}
