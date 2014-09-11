/*
 * BackTrackMutator.h
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#ifndef BACKTRACKMUTATOR_H_
#define BACKTRACKMUTATOR_H_

#include "gntc/GeneticSolver.h"

class BackTrackMutator : public Mutator
{
public:
	BackTrackMutator();
	virtual ~BackTrackMutator();

	void mutate(const City& c, individual child);
};

#endif /* BACKTRACKMUTATOR_H_ */
