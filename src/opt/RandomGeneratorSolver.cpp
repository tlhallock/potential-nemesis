/*
 * RandomGeneratorSolver.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#include "opt/RandomGeneratorSolver.h"
#include "gen/RandomNextGenerator.h"
#include "opt/Cost.h"

RandomGeneratorSolver::RandomGeneratorSolver() {}
RandomGeneratorSolver::~RandomGeneratorSolver() {}

Solution *RandomGeneratorSolver::solve(const std::vector<Request>& requests, const Parameters &p)
{
	RandomNextGenerator gen;

	Solution *s = nullptr;
	Cost *cost = nullptr;

	int count = 0;
	for (;;)
	{
		if (count++ > 1000)
		{
			break;
		}

		Solution *next = gen.generate(requests, p);
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

		std::cout << "Found new solution: " << *next << std::endl;

	}

	return s;
}
