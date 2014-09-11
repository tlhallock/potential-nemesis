/*
 * Optimizer.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_

#include "model/City.h"
#include <vector>


int random_decreasing_probability(int max, double rate = .9);
action_ptr get_close(const Location &current_location, std::vector<action_ptr> *possibles);


void get_necessary_actions(const City &city, Solution *s, sh_time_t start_time,
		const action_ptr& prev_action, const action_ptr& next_request,
		std::vector<action_ptr> &outparam, sh_time_t& outtime,
		const operation_location_constraint& constraints);

#endif /* OPTIMIZER_H_ */
