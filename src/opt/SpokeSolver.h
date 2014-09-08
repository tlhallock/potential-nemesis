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
	action_ptr get_next_request(
			const City &city,
			const Solution *s,
			std::vector<action_ptr> *possibles,
			int driver);
private:

	const Landfill* get_location(const City &c, int i);

	std::vector<const Landfill *> locations;
};

#endif /* SPOKESOLVER_H_ */
