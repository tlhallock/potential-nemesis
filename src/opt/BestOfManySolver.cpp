/*
 * BestOfManySolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/BestOfManySolver.h"
#include "opt/Cost.h"

BestOfManySolver::BestOfManySolver(Solver *delegate_, int max_iters_) :
	Solver {delegate_->get_params()},
	delegate(delegate_),
	max_iters(max_iters_) {}

BestOfManySolver::~BestOfManySolver()
{
	delete delegate;
}

Solution BestOfManySolver::solve(const City &city)
{
	if (delegate == nullptr)
	{
		return Solution {&city};
	}

	Solution s {&city};
	Cost cost;

	int count = 0;
	for (;;)
	{
		if (count++ > max_iters)
		{
			break;
		}

		Solution next = delegate->solve(city);

		Cost another {next};

		if (!(another < cost))
		{
			continue;
		}

		s = next;
		cost = another;

		std::cout << "improved at count = " << count << std::endl;
		count = 0;
	}

	return s;
}

std::string BestOfManySolver::get_name() const
{
	return "best_of_many[" + delegate->get_name() + "]";
}
