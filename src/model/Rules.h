/*
 * Truck.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include "model/Operation.h"
#include "Solution.h"

bool operation_follows(Operation prev_operation, Operation next_operation);

std::vector<action_ptr>* get_possibles(
		Operation prev_operation,
		const Solution *s,
		sh_time_t start_time,
		const Location &current_location,
		const std::vector<action_ptr>& all_possibles);

#endif /* TRUCK_H_ */
