/*
 * SpokeSolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef SPOKESOLVER_H_
#define SPOKESOLVER_H_

#include "opt/NearestPointSolver.h"

class SpokeSolver : public NearestPointSolver
{
public:
	SpokeSolver(const Parameters &p);
	virtual ~SpokeSolver();

	std::string get_name() const;
protected:
	const operation_location_constraint &get_constraints(const City &city, int driver);

private:
	std::vector<operation_location_constraint> constraints;
};

#endif /* SPOKESOLVER_H_ */
