/*
 * SubcycleBreeder.h
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#ifndef SUBCYCLEBREEDER_H_
#define SUBCYCLEBREEDER_H_

#include "gntc/GeneticSolver.h"

class SubcycleBreeder : public Breeder
{
public:
	SubcycleBreeder();
	virtual ~SubcycleBreeder();

	individual breed(const City& c, individual p1, individual p2);
};

#endif /* SUBCYCLEBREEDER_H_ */
