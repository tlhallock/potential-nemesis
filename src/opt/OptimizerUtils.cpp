/*
 * Optimizer.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "OptimizerUtils.h"

#include "model/Rules.h"

#include <stdlib.h>
#include <algorithm>


#define RANDOMNESS 1

int random_decreasing_probability(int max, double rate)
{
#if RANDOMNESS
	for (int i = 0; i < max; i++)
	{
		if ((rand() / (double) RAND_MAX) < rate)
		{
			return i;
		}
	}
	return max - 1;
#else
	return 0;
#endif
}


action_ptr get_close(const Location &current_location, std::vector<action_ptr> *possibles)
{
	std::sort(possibles->begin(), possibles->end(), [&current_location](const action_ptr &i1, const action_ptr &i2)
	{
		sh_time_t t1 = i1->get_time_to(current_location);
		sh_time_t t2 = i2->get_time_to(current_location);
		return t1 < t2;
	});

//	double first = current_location.get_time_to(*possibles->front().get());
//	double last = current_location.get_time_to(*possibles->back().get());
//	std::cout << first << " < " << last << std::endl;

	return possibles->at(random_decreasing_probability(possibles->size()));
}


namespace
{
	void get_matching_sizes(const City& city,
			bool (*filter)(const action_ptr& aptr),
			DumpsterSize prev, DumpsterSize next,
			std::vector<action_ptr> &out)
	{
		const std::vector<action_ptr>& actions = city.get_all_actions();
		auto end = actions.end();
		for (auto it = actions.begin(); it != end; ++it)
		{
			if (prev != (*it)->get_input_dumpster_size())
			{
				continue;
			}
			if (next != (*it)->get_output_dumpster_size())
			{
				continue;
			}
//			if (!operation_follows(prev, (*it)->get_operation()))
//			{
//				continue;
//			}
//			if (!operation_follows((*it)->get_operation(), next))
//			{
//				continue;
//			}

			if (filter != nullptr && filter(*it))
			{
				continue;
			}

			out.push_back(*it);
		}
	}
}

void get_necessary_actions(const City &city, Solution *s, sh_time_t start_time,
		const action_ptr& prev_action, const action_ptr& next_request,
		std::vector<action_ptr> &outparam, sh_time_t& outtime, const operation_location_constraint& constraints)
{
	outparam.clear();

	DumpsterSize prev_size = prev_action->get_output_dumpster_size();
	DumpsterSize next_size = next_request->get_input_dumpster_size();

	Operation prev_op = prev_action->get_operation();
	Operation next_op = next_request->get_operation();

	// There is only one case where you have to do 2 actions to get to the next request...
	if (
			// If you have an empty dumpster,
			(prev_op == Dump || prev_op == UnStore) &&
			// that is a different size than the next one
			(prev_size != next_size && next_size != 0)
			)
	{
		int num_staging_areas = city.get_num_staging_areas();
		for (int i=0; i<num_staging_areas; i++)
		{
			const StagingArea &area = city.get_staging_area(i);

		}

		outtime = sh_time_max;
		return;
	}

	// otherwise we only need to have one link between us...
	outtime = sh_time_max;
	action_ptr minimum_action {nullptr};

	std::vector<action_ptr> middles;
	get_matching_sizes(city, nullptr, prev_size, next_size, middles);

	auto end = middles.end();
	for (auto it = middles.begin(); it != end; ++it)
	{
		const action_ptr &middle_action = *it;
		if (!satisfies_operation_constraint(middle_action, constraints))
		{
			continue;
		}

		if (!is_possible(prev_action, middle_action, start_time, s))
		{
			continue;
		}

		sh_time_t middle_time = middle_action->get_time_taken(start_time, *prev_action.get());
		if (!is_possible(middle_action, next_request, middle_time, s))
		{
			continue;
		}

		sh_time_t end_time = next_request->get_time_taken(start_time, *middle_action.get());
		if (end_time >= outtime)
		{
			continue;
		}

		outtime = end_time;
		minimum_action = middle_action;
	}

	if (outtime == sh_time_max)
	{
		return;
	}

//	std::cout << "To get from " << *prev_action.get() << " \nto " << *next_request.get() << "\n we need a " << *minimum_action.get() << std::endl << std::endl << std::endl;

	outparam.push_back(minimum_action);
	outparam.push_back(next_request);
}
