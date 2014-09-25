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
		int driver,
		const Action* action,
		sh_time_t &end_time,
		bool verbose)
{
	sh_time_t start_time = s->get_route(driver).get_time_to_end();
	const Action* prev_action = s->get_route(driver).get_last_action();

	return is_possible(city, s, start_time, prev_action, action, end_time, verbose);
}

bool is_possible(const City* city,
		const Solution * s,
		int driver,
		std::vector<int> intermediates,
		sh_time_t& out_time,
		bool verbose)
{
	int nints = intermediates.size();

	const Action* prev_action;
	const Action* next_action = s->get_route(driver).get_last_action();

	for (int i = 0; i < nints; i++)
	{
		for (int j = 0; j < nints; j++)
		{
			if (i != j && intermediates.at(i) == intermediates.at(j))
			{
				return false;
			}
		}
	}

	out_time = sh_time_max;
	sh_time_t start_time = s->get_route(driver).get_time_to_end();

	int size = intermediates.size();
	for (int i = 0; i < size; i++)
	{
		prev_action = next_action;
		next_action = city->get_stop(intermediates.at(i));

		if (!is_possible(city, s, start_time, prev_action, next_action, out_time, verbose))
		{
			return false;
		}

		start_time = out_time;
	}
	return true;
}

bool is_possible(const City* city,
		const Solution * s,
		const sh_time_t start_time,
		const Action* prev_action,
		const Action* next_action,
		sh_time_t &out_time,
		bool verbose)
{
	out_time = get_time_taken(city, start_time, prev_action->get_location(), next_action);

//	if (out_time > sh_time_look_ahead)
//	{
//		if (verbose)
//		{
//			std::cout << "past last possible time" << std::endl;
//		}
//		return false;
//	}
	if (!operation_follows(prev_action->get_operation(), next_action->get_operation()))
	{
		if (verbose)
		{
			std::cout << "operations do not follow" << std::endl;
		}
		return false;
	}
	if (!follows_in_time(out_time,  next_action))
	{
		if (verbose)
		{
			std::cout << "bad time" << std::endl;
		}
		return false;
	}
	if (s->already_serviced(next_action))
	{
		if (verbose)
		{
			std::cout << "already serviced" << std::endl;
		}
//			std::cout << "\n already serviced = " << next_action->get_index() << std::endl;
		return false;
	}
	if (!sizes_match(prev_action, next_action))
	{
		if (verbose)
		{
			std::cout << "wrong size" << std::endl;
		}
		return false;
	}

	return true;
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

		sh_time_t end_time;

		if (is_possible(&city, s, start_time, prev_action, possible, end_time))
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

bool follows_in_time(const sh_time_t end_time, const Action* to)
{
	return
#if 0
			end_time > to->get_minimum_time() &&
#endif
			end_time < to->get_maximum_time();
}

