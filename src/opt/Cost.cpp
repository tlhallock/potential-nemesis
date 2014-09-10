/*
 * Cost.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Cost.h"

#include "Solution.h"

Cost::Cost(const Solution &s) :
	num_serviced(s.get_num_requests_serviced()),
	time(s.get_time_taken()) {}

Cost::Cost() :
	num_serviced(0),
	time(sh_time_max) {}

Cost::Cost(const std::shared_ptr<Solution> &s) :
	num_serviced(s->get_num_requests_serviced()),
	time(s->get_time_taken()) {}

Cost::~Cost() {}


bool Cost::is_better_than(const Cost &other) const
{
	if (num_serviced > other.num_serviced)
	{
		return true;
	}
	else if (other.num_serviced > num_serviced)
	{
		return false;
	}

	if (time < other.time)
	{
		return true;
	}

	return false;
}

int Cost::get_number_serviced() const
{
	return num_serviced;
}

bool Cost::operator <(const Cost& other)
{
	return is_better_than(other);
}
