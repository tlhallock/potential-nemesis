/*
 * GreedyMutator.h
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#ifndef GREEDYMUTATOR_H_
#define GREEDYMUTATOR_H_

#include "gntc/GeneticSolver.h"

class GreedyMutator : public Mutator
{
public:
	GreedyMutator(int num_subs);
	virtual ~GreedyMutator();

	void mutate(const City& c, individual child);
private:
	int num_subs;
};

#endif /* GREEDYMUTATOR_H_ */
