/*
 * Solver.h
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "model/Request.h"
#include "Parameters.h"
#include "Solution.h"

#include <vector>

class Solver
{
public:
	Solver();
	virtual ~Solver();

	virtual Solution *solve(const std::vector<Request>& requests, const Parameters &p) = 0;
};

#endif /* SOLVER_H_ */
