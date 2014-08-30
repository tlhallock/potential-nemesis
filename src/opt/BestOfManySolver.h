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
	BestOfManySolver(const Parameters &p, Solver *delegate, int max_iters);
	virtual ~BestOfManySolver();

	Solution *solve(const std::vector<Request>& requests);
	std::string get_name() const;
private:
	Solver *delegate;
	int max_iters;
};

#endif /* BESTOFMANYSOLVER_H_ */
