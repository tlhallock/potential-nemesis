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

bool is_possible(const action_ptr prev_action,
		const action_ptr action,
		const sh_time_t start_time, const Solution * const s);

std::vector<action_ptr>* get_possibles(
		const Solution *s,
		sh_time_t start_time,
		const action_ptr &prev_action,
		const std::vector<action_ptr>& all_possibles);

#endif /* TRUCK_H_ */
