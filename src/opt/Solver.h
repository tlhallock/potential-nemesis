/*
 * Solver.h
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#ifndef SOLVER_H_
#define SOLVER_H_

#include "model/City.h"
#include "Parameters.h"
#include "Solution.h"

#include <vector>

class Solver
{
public:
	Solver(const Parameters &p);
	virtual ~Solver();

	virtual Solution *solve(const City &city) = 0;
	virtual std::string get_name() const = 0;

	const Parameters get_params() const;
protected:
	const Parameters &p;
};

#endif /* SOLVER_H_ */
