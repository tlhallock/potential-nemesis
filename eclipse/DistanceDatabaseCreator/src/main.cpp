/*
 * main.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "DistanceSetSet.h"

#include <iostream>
#include <fstream>

#include <float.h>


int main(int argc, char **argv)
{
	srand(time(nullptr));

	DistanceSetSet s {"/work/potential-nemesis/python/examples/list.txt"};

	std::cout << "Found " << s.get_num_points() << " different points." << std::endl << std::endl;
	std::cout << "time/coord = " << s.get_average_time_per_coord() << std::endl << std::endl;
	std::cout << "time/meter = " << s.get_average_time_per_meter() << " (" << (1/s.get_average_time_per_meter()*2.23694) << " mi/h)" <<std::endl << std::endl;
	std::cout << "avg cost = " << s.get_average_cost(10000) * s.get_average_time_per_coord() / 60 << " min" << std::endl << std::endl;
	std::cout << "avg time = " << s.get_average_time(10000) / 60 << " min" << std::endl << std::endl;

	Point lower;
	Point upper;

	s.find_bounds(lower, upper);
	std::cout << "bounds: " << lower << " to " << upper << std::endl;

	Point p1 = get_random_point(lower, upper);
	Point p2 = get_random_point(lower, upper);

	std::cout << "to search: " << p1 << " to " << p2 << std::endl;

	Guess g = s.get_best_guess(p1, p2);
	std::cout << "Guess: " << g << std::endl;

	return 0;
}
