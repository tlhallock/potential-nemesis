/*
 * Optimizer.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_

#include "model/City.h"
#include "Solution.h"

#include "model/Constraint.h"

#include <vector>


int random_decreasing_probability(int max, double rate = .9);
const Action* get_close(const City* city, location l,  std::vector<const Action* > *possibles);


 void get_best_intermediate(
			const City &city,
			Solution *s,
			int driver,
			int to,

			const operation_location_constraint& constraints,

			std::vector<int>& outparam,
			sh_time_t& outtime);

#endif /* OPTIMIZER_H_ */
