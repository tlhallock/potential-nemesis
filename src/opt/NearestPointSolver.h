/*
 * NearestPointSolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef NEARESTPOINTSOLVER_H_
#define NEARESTPOINTSOLVER_H_

#include "opt/ForDriverForStopSolver.h"

class NearestPointSolver : public ForDriverForStopSolver
{
public:
	NearestPointSolver(const Parameters &p);
	~NearestPointSolver();

	std::string get_name() const;
protected:
	action_ptr get_next_request(
			const City &city,
			const Solution *s,
			std::vector<action_ptr> *possibles,
			int driver);
};

#endif /* NEARESTPOINTSOLVER_H_ */
