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
	int get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver);
};

#endif /* NEARESTPOINTSOLVER_H_ */
