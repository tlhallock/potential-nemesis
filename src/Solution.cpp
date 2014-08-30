/*
 * Solution.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Solution.h"

Solution::Solution(int num_drivers)
{
	for (int i = 0; i < num_drivers; i++)
	{
		routes.push_back(new Route);
	}
}

Solution::~Solution()
{
	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		delete routes.at(i);
	}
}

sh_time_t Solution::get_time_taken() const
{
	sh_time_t max = 0;

	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		sh_time_t another = routes.at(i)->get_time_taken();
		if (another > max)
		{
			max = another;
		}
	}

	return max;
}

int Solution::get_num_requests_serviced() const
{
	sh_time_t sum = 0;

	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		sum += routes.at(i)->get_num_requests_serviced();
	}

	return sum;
}

Route& Solution::get_route(int index) const
{
	return *routes.at(index);
}

int Solution::get_num_drivers() const
{
	return routes.size();
}

std::ostream& operator<<(std::ostream& os, const Solution& r)
{
	int num_drivers = r.get_num_drivers();
	os << "Num drivers: " << r.get_num_drivers() << " t=" << r.get_time_taken() << " n=" << r.get_num_requests_serviced() << std::endl;

	for (int i = 0; i < num_drivers; i++)
	{
		os << "Route [" << i << "]:\n" << r.get_route(i);
	}

	return os;
}

