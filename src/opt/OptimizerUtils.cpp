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


const Action* get_close(const City *city, sh_time_t start_time, location from, std::vector<const Action*> *possibles)
{
	std::sort(possibles->begin(), possibles->end(), [city, start_time, &from](const Action* i1, const Action* i2)
	{
		sh_time_t t1 = get_time_taken(city, start_time, from, i1);
		sh_time_t t2 = get_time_taken(city, start_time, from, i2);
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
			bool (*filter)(const City& city, const Action* aptr),
			DumpsterSize prev, DumpsterSize next,
			std::vector<const Action* > &out)
	{
		const std::vector<const Action *>& actions = city.get_all_stops();
		int end = actions.size();

		for (int i=0; i<end;i++)
		{
			const Action* action = actions.at(i);
			if (prev != action->get_input_dumpster_size())
			{
				continue;
			}
			if (next != action->get_output_dumpster_size())
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

			if (filter != nullptr && filter(city, action))
			{
				continue;
			}

			out.push_back(action);
		}
	}
}

void get_necessary_actions(const City &city, Solution *s, sh_time_t start_time,
		const Action* prev_action, const Action* next_request,
		std::vector<const Action* > &outparam, sh_time_t& outtime, const operation_location_constraint& constraints)
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
#if 0
		int num_staging_areas = city.get_num_staging_areas();
		for (int i=0; i<num_staging_areas; i++)
		{
			const StagingArea &area = city.get_staging_area(i);

		}

		outtime = sh_time_max;
#endif
		return;
	}

	// otherwise we only need to have one link between us...
	outtime = sh_time_max;
	const Action* minimum_action = nullptr;

	std::vector<const Action* > middles;
	get_matching_sizes(city, nullptr, prev_size, next_size, middles);

	auto end = middles.end();
	for (auto it = middles.begin(); it != end; ++it)
	{
		const Action* middle = *it;
		if (!satisfies_operation_constraint(middle, constraints))
		{
			continue;
		}

		if (!is_possible(&city, s, start_time, prev_action, middle))
		{
			continue;
		}

		sh_time_t middle_time = get_time_taken(&city, start_time, prev_action->get_location(), middle);
		if (!is_possible(&city, s, middle_time, middle, next_request))
		{
			continue;
		}

		sh_time_t end_time = get_time_taken(&city, start_time, middle->get_location(), next_request);
		if (end_time >= outtime)
		{
			continue;
		}

		outtime = end_time;
		minimum_action = middle;
	}

	if (outtime == sh_time_max)
	{
		return;
	}

//	std::cout << "To get from " << *prev_action.get() << " \nto " << *next_request.get() << "\n we need a " << *minimum_action.get() << std::endl << std::endl << std::endl;

	outparam.push_back(minimum_action);
	outparam.push_back(next_request);
}
