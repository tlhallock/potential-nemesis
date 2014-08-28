/*
 * RandomGeneratorSolver.h
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#ifndef RANDOMGENERATORSOLVER_H_
#define RANDOMGENERATORSOLVER_H_

#include "opt/Solver.h"

class RandomGeneratorSolver : public Solver
{
public:
	RandomGeneratorSolver();
	virtual ~RandomGeneratorSolver();

	Solution *solve(const std::vector<Request>& requests, const Parameters &p);
};

#endif /* RANDOMGENERATORSOLVER_H_ */
