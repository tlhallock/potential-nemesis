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

void backtrack_necessary_actions(
		const City &city, Solution *s, sh_time_t start_time,
		const Action* prev_action, const Action* next_request,


		std::vector<const Action* > &outparam, sh_time_t& outtime,
		const operation_location_constraint& constraints)
{

}

void get_best_intermediate(
		const City &city,
		Solution *s,
		int driver,
		int to,

		const operation_location_constraint& constraints,

		std::vector<int>& outparam,
		sh_time_t& outtime)
{
	int from = s->get_route(driver).get_last_action()->get_index();

	Operation op = s->get_route(driver).get_last_action()->get_operation();
	if (op == Store || op == UnStore || op == Dump)
	{
		outparam.clear();
		const Action* action = city.get_stop(to);
		if (is_possible(&city, s, driver, action, outtime))
		{
			outparam.push_back(to);
		}

#if 0
		// not at request, get to one...
		const std::vector<int> requests = city.get_requests();
		int rsize = requests.size();
		for (int i = 0; i < rsize; i++)
		{
			sh_time_t end_time;
			const Action* action = city.get_stop(requests.at(i));
			if (!is_possible(&city, s, driver, action, end_time))
			{
				continue;
			}
			if (end_time < outtime)
			{
				outparam.clear();
				outparam.push_back(action->get_index());
				outtime = end_time;
			}
		}
#endif
		return;
	}
	op = city.get_stop(to)->get_operation();
	if (op == Store || op == UnStore || op == Dump)
	{
		std::cout << "Unable to get intermediates to a non-request!! (" << operation_to_string(op) << ")" << std::endl;
		die();
	}

	outparam.clear();
	outtime = sh_time_max;

	const IntermediateAction *inter = city.get_intermediates(from, to);
	if (inter == nullptr)
	{
		return;
	}

	auto end = inter->get_alternatives().end();
	for (auto it = inter->get_alternatives().begin(); it != end; ++it)
	{
		const std::vector<int>& path = *it;

		sh_time_t end_time;
		if (!is_possible(&city, s, driver, path, end_time))
		{
			continue;
		}

		if (end_time < outtime)
		{
			outparam = path;
			outtime = end_time;
		}
	}
}



#if 0

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
	const Action* minimum_action = nullptr;

	std::vector<const Action* > middles;
	get_matching_sizes(city, nullptr, prev_size, next_size, middles);

	auto end = middles.end();
	for (auto it = middles.begin(); it != end; ++it)
	{
		const Action* middle = *it;

//		std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
//		std::cout << "Trying to find link between \n" << *prev_action << "\n at t=" << start_time << "\n and  \n" << *next_request << std::endl;
//		std::cout << "It has to beat " << outtime << std::endl;
//		std::cout << "Considering \n" << *middle << std::endl;

		if (!satisfies_operation_constraint(middle, constraints))
		{
//			std::cout << "no 0" << std::endl;
			continue;
		}

		if (!is_possible(&city, s, start_time, prev_action, middle))
		{
//			std::cout << "no 1" << std::endl;
			continue;
		}

		sh_time_t middle_time = get_time_taken(&city, start_time, prev_action->get_location(), middle);
//		std::cout << "m=" << middle_time << std::endl;
		if (!is_possible(&city, s, middle_time, middle, next_request))
		{
//			std::cout << "no 2" << std::endl;
			continue;
		}

		sh_time_t end_time = get_time_taken(&city, middle_time, middle->get_location(), next_request);
//		std::cout << "e=" << end_time << std::endl;
		if (end_time >= outtime)
		{
//			std::cout << "no 3" << std::endl;
			continue;
		}

//		std::cout << "yes" << std::endl;

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
#endif
