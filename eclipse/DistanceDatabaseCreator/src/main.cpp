/*
 * main.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "DistanceSetSet.h"


#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <algorithm>
#include <sstream>

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

	// Denver lower bound:  39.558185, -105.226243
	// Denver upper bound:  40.211516, -104.745591

	s.find_bounds(lower, upper);
	std::cout << "bounds: " << lower << " to " << upper << std::endl;

	Point p1 = get_random_point(lower, upper);
	Point p2 = get_random_point(lower, upper);

	std::cout << "to search: " << p1 << " to " << p2 << std::endl;

	std::cout << "Euclidean distance: " << p1.get_euclidean_distance(p2) << std::endl << std::endl;

	std::cout << "Guess: " << s.get_best_guess(p1, p2) << std::endl << std::endl;


	std::vector<std::string> output;
	for (int i = 0; i < 10; i++)
	{
		p1 = get_random_point(lower, upper);
		p2 = get_random_point(lower, upper);
		Guess cost = s.get_best_guess(p1, p2);

		std::stringstream ss;
		ss << std::left << std::setw(12) << p1.get_euclidean_distance(p2) << " - "
				<< std::left << std::setw(12) << cost.get_answer() << " - "
				<< std::left << std::setw(12) << cost.get_cost();
		output.push_back(ss.str());
	}
	std::cout << "Euclidean    - Time         - Cost" << std::endl;
	std::sort(output.begin(), output.end(), [](const std::string &s1, const std::string &s2) { return s1 < s2; });
	std::for_each(output.begin(), output.end(), [](const std::string &s) { std::cout << s << std::endl; });

	return 0;
}
