/*
 * ForDriverForStopSolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef FORDRIVERFORSTOPSOLVER_H_
#define FORDRIVERFORSTOPSOLVER_H_

#include "opt/Solver.h"

class ForDriverForStopSolver : public Solver
{
public:
	ForDriverForStopSolver(const Parameters &p);
	~ForDriverForStopSolver();

	Solution *solve(const std::vector<Request>& requests);
protected:
	virtual int get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver) = 0;
};

#endif /* FORDRIVERFORSTOPSOLVER_H_ */
