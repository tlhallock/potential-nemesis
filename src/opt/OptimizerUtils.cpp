/*
 * Optimizer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "OptimizerUtils.h"

#include <stdlib.h>

int random_decreasing_probability(int max, double rate)
{
	for (int i = 0; i < max; i++)
	{
		if ((rand() % RAND_MAX) < rate)
		{
			return i;
		}
	}
	return max - 1;
}
