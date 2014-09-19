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
#include <vector>


int random_decreasing_probability(int max, double rate = .9);
const Action* get_close(const City* city, location l,  std::vector<const Action* > *possibles);


void get_necessary_actions(const City &city, Solution *s, sh_time_t start_time,
		const Action* prev_action, const Action* next_request,
		std::vector<const Action*> &outparam, sh_time_t& outtime,
		const operation_location_constraint& constraints);

#endif /* OPTIMIZER_H_ */
