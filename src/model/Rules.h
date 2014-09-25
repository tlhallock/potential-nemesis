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


bool follows_in_time(const sh_time_t end_time, const Action* to);

sh_time_t get_time_taken(const City *city, sh_time_t start_time, location from, const Action* to);

bool is_possible(const City* city,
		const Solution * s,
		int driver,
		const Action* action,
		sh_time_t &out_time,
		bool verbose = false);

bool is_possible(const City* city,
		const Solution * s,
		const sh_time_t start_time,
		const Action* prev_action,
		const Action* action,
		sh_time_t &out_time,
		bool verbose = false);

bool is_possible(const City* city,
		const Solution * s,
		int driver,
		std::vector<int> intermediates,
		sh_time_t& out_time,
		bool verbose = false);

std::vector<const Action*>* get_possibles(
		const Solution *s,
		sh_time_t start_time,
		const Action* prev_action,
		const City &city);

#endif /* TRUCK_H_ */
