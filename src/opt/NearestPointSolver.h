/*
 * NearestPointSolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef NEARESTPOINTSOLVER_H_
#define NEARESTPOINTSOLVER_H_

#include "opt/ForDriverForStopSolver.h"

#include <map>

class NearestPointSolver : public ForDriverForStopSolver
{
public:
	NearestPointSolver(const Parameters &p);
	~NearestPointSolver();

	std::string get_name() const;
protected:
	bool get_next_request(
			const City &city,
			Solution *s,
			int driver);

	const operation_location_constraint &get_constraints(const City& city, int driver);
	const operation_location_constraint no_constraints;
};

#endif /* NEARESTPOINTSOLVER_H_ */
