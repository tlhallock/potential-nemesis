/*
 * Cost.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef COST_H_
#define COST_H_

#include "common.h"

class Solution;

class Cost
{
public:
	Cost(const Solution &s);
	Cost();
	~Cost();

	bool is_better_than(const Cost *other);
private:
	int num_serviced;
	sh_time_t time;
};

#endif /* COST_H_ */
