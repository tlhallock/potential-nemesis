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

	Solution solve(const City &city);
protected:
	virtual action_ptr get_next_request(
			const City &city,
			const Solution *s,
			std::vector<action_ptr> *possibles,
			int driver) = 0;
};

#endif /* FORDRIVERFORSTOPSOLVER_H_ */
