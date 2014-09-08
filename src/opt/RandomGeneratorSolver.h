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
	action_ptr get_next_request(
			const City &city,
			const Solution *s,
			std::vector<action_ptr> *possibles,
			int driver);
};

#endif /* RANDOMGENERATORSOLVER_H_ */
