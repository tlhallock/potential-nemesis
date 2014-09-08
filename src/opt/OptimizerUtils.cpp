/*
 * Optimizer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "OptimizerUtils.h"

#include <stdlib.h>
#include <algorithm>


#define RANDOMNESS 1

int random_decreasing_probability(int max, double rate)
{
#if RANDOMNESS
	for (int i = 0; i < max; i++)
	{
		if ((rand() / (double) RAND_MAX) < rate)
		{
			return i;
		}
	}
	return max - 1;
#else
	return 0;
#endif
}


action_ptr get_close(const Location &current_location, std::vector<action_ptr> *possibles)
{
	std::sort(possibles->begin(), possibles->end(), [&current_location](const action_ptr &i1, const action_ptr &i2)
	{
		sh_time_t t1 = i1->get_time_to(current_location);
		sh_time_t t2 = i2->get_time_to(current_location);
		return t1 < t2;
	});

//	double first = current_location.get_time_to(*possibles->front().get());
//	double last = current_location.get_time_to(*possibles->back().get());
//	std::cout << first << " < " << last << std::endl;

	return possibles->at(random_decreasing_probability(possibles->size()));
}
