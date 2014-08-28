/*
 * Solution.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Route.h"

class Solution
{
public:
	Solution(int num_drivers);
	~Solution();

	sh_time_t get_time_taken() const;
	int get_num_requests_serviced() const;

	int get_num_drivers() const;
	Route &get_route(int index) const;

	friend std::ostream& operator<<(std::ostream& os, const Solution& r);
private:
	std::vector<Route *> routes;
};

#endif /* SOLUTION_H_ */
