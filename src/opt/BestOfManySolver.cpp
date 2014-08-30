/*
 * BestOfManySolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/BestOfManySolver.h"
#include "opt/Cost.h"

BestOfManySolver::BestOfManySolver(const Parameters &p, Solver *delegate_, int max_iters_) :
	Solver {p},
	delegate(delegate_),
	max_iters(max_iters_) {}

BestOfManySolver::~BestOfManySolver()
{
	delete delegate;
}

Solution* BestOfManySolver::solve(const std::vector<Request>& requests)
{
	if (delegate == nullptr)
	{
		return nullptr;
	}

	Solution *s = nullptr;
	Cost *cost = nullptr;

	int count = 0;
	for (;;)
	{
		if (count++ > max_iters)
		{
			break;
		}

		Solution *next = delegate->solve(requests);
		Cost *another = new Cost{*next};

		if (!another->is_better_than(cost))
		{
			delete next;
			delete another;
			continue;
		}

		delete s;
		s = next;
		delete cost;
		cost = another;

		count = 0;
	}

	return s;
}

std::string BestOfManySolver::get_name() const
{
	return "best_of_many";
}
