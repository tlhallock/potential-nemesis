/*
 * NearestPointSolver.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#include "opt/NearestPointSolver.h"

#include "opt/OptimizerUtils.h"
#include "model/Rules.h"

#include <algorithm>

namespace
{
	class TimeTo
	{
	public:
		TimeTo () {}
		~TimeTo() {}

		sh_time_t time_taken;
		std::vector<const Action*> actions;

		bool operator<(const TimeTo &other) const
		{
			return time_taken;
		}
	};
}

NearestPointSolver::NearestPointSolver(const Parameters &p) : ForDriverForStopSolver(p) {}
NearestPointSolver::~NearestPointSolver() {}

bool NearestPointSolver::get_next_request(
		const City &city,
		Solution *s,
		int driver)
{
	std::vector<TimeTo*> times;

	Route& route = s->get_route(driver);

	sh_time_t start_time = route.get_time_to_end();
	const Action* prev_action = route.get_last_action();

	int num_stops = city.get_num_stops();
	for (int i = 0; i < num_stops; i++)
	{
		const Action* next_action = city.get_stop(i);
		if (is_possible(&city, s, start_time, prev_action, next_action))
		{
			if (!satisfies_operation_constraint(next_action, get_constraints(city, driver)))
			{
				continue;
			}

			TimeTo *best = new TimeTo;
			best->time_taken = start_time;
			best->actions.push_back(next_action);
			times.push_back(best);
			continue;
		}

		TimeTo *best = new TimeTo;

		get_necessary_actions(city, s, start_time,
				prev_action, next_action,
				best->actions, best->time_taken,
				get_constraints(city, driver));

		if (best->time_taken == sh_time_max)
		{
			delete best;
			continue;
		}

		times.push_back(best);
	}

	if (times.size() == 0)
	{
		return false;
	}

	std::sort(times.begin(), times.end(), [](const TimeTo * const i1, const TimeTo * const i2)
	{
		return i1->time_taken < i2->time_taken;
	});

	TimeTo *best = times.at(random_decreasing_probability(times.size()));
	for (int i = 0; i < (int) best->actions.size(); i++)
	{
		s->service_next(driver, best->actions.at(i));
	}

	std::for_each(times.begin(), times.end(), [](const TimeTo * const i) { delete i; });

	return true;
}

std::string NearestPointSolver::get_name() const
{
	return "nearest";
}

const operation_location_constraint &NearestPointSolver::get_constraints(const City& city, int driver)
{
	return no_constraints;
}
