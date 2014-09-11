/*
 * CycleMutator.h
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#ifndef CYCLEMUTATOR_H_
#define CYCLEMUTATOR_H_

#include "gntc/GeneticSolver.h"

class CycleMutator : public Mutator
{
public:
	CycleMutator();
	virtual ~CycleMutator();

	void mutate(const City& c, individual child);
};

#endif /* CYCLEMUTATOR_H_ */
