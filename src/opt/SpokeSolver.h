/*
 * SpokeSolver.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef SPOKESOLVER_H_
#define SPOKESOLVER_H_

#include "opt/ForDriverForStopSolver.h"

class SpokeSolver : public ForDriverForStopSolver
{
public:
	SpokeSolver(const Parameters &p);
	virtual ~SpokeSolver();

	std::string get_name() const;
protected:
	int get_next_request(const std::vector<Request>& originals, std::vector<int> &possibles, const Solution *s, int driver);
private:
	std::vector<Location> locations;
};

#endif /* SPOKESOLVER_H_ */
