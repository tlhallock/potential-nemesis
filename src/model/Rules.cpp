/*
 * Truck.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Rules.h"

#include <iostream>


typedef enum
{
	NoDumpster,
	EmptyDumpster,
	FullDumpster,
} TruckState;


TruckState operation_to_truck_state(Operation o)
{
	switch (o)
	{
		case PickUp:
			return FullDumpster;
		case DropOff:
			return NoDumpster;
		case Dump:
			return EmptyDumpster;
		case Store:
			return NoDumpster;
		case UnStore:
			return EmptyDumpster;
		case Replace:
			return FullDumpster;
		default:
			std::cout << "Never reach here." << std::endl;
			return EmptyDumpster;
	}
}


bool operation_follows(Operation prev_operation, Operation next_operation)
{
	switch (operation_to_truck_state(prev_operation))
	{
		case NoDumpster:
			return next_operation == PickUp
					|| (next_operation == UnStore && prev_operation != Store);
		case EmptyDumpster:
			return next_operation == DropOff
					|| next_operation == Replace
					|| (next_operation == Store && prev_operation != UnStore);
		case FullDumpster:
			return next_operation == Dump;
		default:
			std::cout << "Should never reach this code." << std::endl;
			return false;
	}
}



std::vector<action_ptr>* get_possibles(
		Operation prev_operation,
		const Solution *s,
		sh_time_t start_time,
		const Location &current_location,
		const std::vector<action_ptr>& all_possibles)
{
	std::vector<action_ptr> *actions = new std::vector<action_ptr>;

	auto end = all_possibles.end();
	for (auto it = all_possibles.begin(); it != end; ++it)
	{
		const action_ptr &action = *it;
		if (            operation_follows(prev_operation, action->get_operation())
				&& action->follows_in_time(start_time, current_location)
				&& !s->already_serviced(action))
		{
			actions->push_back(action);
		}
	}
	return actions;
}
