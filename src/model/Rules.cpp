/*
 * Truck.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Rules.h"

#include <iostream>

namespace deleteme
{

typedef enum
{
	NoDumpster,
	EmptyDumpster,
	FullDumpster,
} TruckState;


inline TruckState operation_to_truck_state(Operation o)
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

bool old_operation_follows(Operation prev_operation, Operation next_operation)
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


}

inline bool sizes_match(const action_ptr &a1, const action_ptr &a2)
{
	return a1->get_output_dumpster_size() == a2->get_input_dumpster_size();
}


inline bool operation_follows(Operation prev_operation, Operation next_operation)
{
	switch (prev_operation)
	{
		case Store:
		case DropOff:
			return next_operation == PickUp
					|| next_operation == UnStore;
		case UnStore:
		case Dump:
			return next_operation == DropOff
					|| next_operation == Replace
					|| next_operation == Store;
		case PickUp:
		case Replace:
			return next_operation == Dump;
		default:
			std::cout << "Should never reach this code." << std::endl;
			return false;
	}
}

bool is_possible(const action_ptr prev_action, const action_ptr action, const sh_time_t start_time, const Solution * const s)
{
	return		start_time < sh_time_look_ahead
			&& operation_follows(prev_action->get_operation(), action->get_operation())
			&& action->follows_in_time(start_time, *prev_action.get())
			&& !s->already_serviced(action)
			&& sizes_match(prev_action, action);
}

std::vector<action_ptr>* get_possibles(
		const Solution *s,
		sh_time_t start_time,
		const action_ptr& prev_action,
		const std::vector<action_ptr>& all_possibles)
{
	std::vector<action_ptr> *actions = new std::vector<action_ptr>;

	auto end = all_possibles.end();
	for (auto it = all_possibles.begin(); it != end; ++it)
	{
		const action_ptr &action = *it;

//		std::cout << "Prev " << *prev_action.get() << std::endl;
//		std::cout << "Consider " << *action.get() << std::endl;

		if (is_possible(prev_action, action, start_time, s))
		{
			actions->push_back(action);
		}
	}
	return actions;
}
