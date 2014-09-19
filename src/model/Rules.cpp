/*
 * Truck.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Rules.h"
#include "model/City.h"

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

inline bool sizes_match(const Action* a1, const Action* a2)
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

bool is_possible(const City* city,
		const Solution * s,
		const sh_time_t start_time,
		const Action* prev_action,
		const Action* action)
{
	return          start_time < sh_time_look_ahead
			&& operation_follows(prev_action->get_operation(), action->get_operation())
			&& follows_in_time(city, start_time, prev_action->get_location(), action)
			&& !s->already_serviced(action)
			&& sizes_match(prev_action, action);
}

std::vector<const Action*>* get_possibles(
		const Solution *s,
		sh_time_t start_time,
		const Action* prev_action,
		const City &city)
{
	std::vector<const Action*> *actions = new std::vector<const Action*>;

	const std::vector<const Action*> &all_possibles = city.get_all_stops();

	auto end = all_possibles.end();
	for (auto it = all_possibles.begin(); it != end; ++it)
	{
		const Action* possible = *it;

//		std::cout << "Prev " << *prev_action.get() << std::endl;
//		std::cout << "Consider " << *action.get() << std::endl;

		if (is_possible(&city, s, start_time, prev_action, possible))
		{
			actions->push_back(possible);
		}
	}
	return actions;
}



sh_time_t get_time_taken(const City *city, sh_time_t start_time, location from, const Action* to)
{
	sh_time_t end_time = start_time;
	end_time += city->get_time_from(from, to->get_location());
	if (end_time < to->get_minimum_time())
	{
		end_time = to->get_minimum_time();
	}
	end_time += to->get_wait_time();

	return end_time;
}

bool follows_in_time(const City *city, sh_time_t start_time, location from, const Action* to)
{
	sh_time_t time = get_time_taken(city, start_time, from, to);
	return
#if 0
			time > to->get_minimum_time() &&
#endif
			time < to->get_maximum_time();
}

