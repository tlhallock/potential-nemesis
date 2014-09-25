/*
 * BestOfManySolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef BESTOFMANYSOLVER_H_
#define BESTOFMANYSOLVER_H_

#include "opt/Solver.h"

class BestOfManySolver : public Solver
{
public:
	BestOfManySolver(Solver *delegate, int max_iters);
	~BestOfManySolver();

	Solution solve(const City &city);
	std::string get_name() const;
private:
	Solver *delegate;
	int max_iters;
};

#endif /* BESTOFMANYSOLVER_H_ */
