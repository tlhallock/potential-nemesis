/*
 * Cost.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef COST_H_
#define COST_H_

#include "common.h"

#include <memory>

class Solution;

class Cost
{
public:
	Cost();
	Cost(const Solution &s);
	Cost(const std::shared_ptr<Solution> &s);
	~Cost();

	bool is_better_than(const Cost &other) const;

	int get_number_serviced() const;

	bool operator< (const Cost &other);
private:
	int num_serviced;
	sh_time_t time;
};

#endif /* COST_H_ */
