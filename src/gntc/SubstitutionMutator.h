/*
 * SubstitutionMutator.h
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#ifndef SUBSTITUTIONMUTATOR_H_
#define SUBSTITUTIONMUTATOR_H_

#include "gntc/GeneticSolver.h"

class SubstitutionMutator : public Mutator
{
public:
	SubstitutionMutator(Solver *slvr);
	virtual ~SubstitutionMutator();

	void mutate(const City& c, individual child);
private:
	Solver *slvr;
};

#endif /* SUBSTITUTIONMUTATOR_H_ */
