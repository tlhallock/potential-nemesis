/*
 * GeneticSolver.h
 *
 *  Created on: Sep 9, 2014
 *      Author: thallock
 */

#ifndef GENETICSOLVER_H_
#define GENETICSOLVER_H_

#include "opt/Solver.h"

#include <memory>

#define BOOT_STRAP_SIZE 20

typedef std::shared_ptr<Solution> individual;

class Mutator
{
public:
	Mutator();
	virtual ~Mutator();
	virtual void mutate(const City& c, individual child);
};
class Breeder
{
public:
	Breeder();
	virtual ~Breeder();
	virtual individual breed(const City& c, individual p1, individual p2);
};
class Selector
{
public:
	Selector();
	virtual ~Selector();
	virtual void select(const City& c, std::vector<individual> &population, individual new_child, int pop_size);
	virtual individual get_best(const City& c, std::vector<individual> &population);
};

class GeneticSolver : public Solver
{
public:
	GeneticSolver(  const Parameters &p,
			int stable_threshold,
			Solver *delegate_ = nullptr,
			int population_size_ = 50,
			Breeder *b = nullptr,
			Mutator *m = nullptr,
			Selector *s = nullptr);

	virtual ~GeneticSolver();

	Solution solve(const City &city);

	std::string get_name() const;
private:
	std::vector<individual> population;
	int population_size;
	int stable_threshold;

	Solver *delegate;
	Mutator *mutator;
	Breeder *breeder;
	Selector *selector;
};

#endif /* GENETICSOLVER_H_ */
