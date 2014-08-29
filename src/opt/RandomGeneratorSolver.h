/*
 * RandomGeneratorSolver.h
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#ifndef RANDOMGENERATORSOLVER_H_
#define RANDOMGENERATORSOLVER_H_

#include "opt/ForDriverForStopSolver.h"

class RandomGeneratorSolver : public ForDriverForStopSolver
{
public:
	RandomGeneratorSolver(const Parameters &p);
	virtual ~RandomGeneratorSolver();

	std::string get_name() const;
protected:
	int get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver);
};

#endif /* RANDOMGENERATORSOLVER_H_ */
