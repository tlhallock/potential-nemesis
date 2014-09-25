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
		TimeTo () : time_taken{sh_time_max} {}
		~TimeTo() {}

		sh_time_t time_taken;
		std::vector<int> actions;

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


	const std::vector<int>& requests = city.get_requests();

	int num_stops = requests.size();
	for (int i = 0; i < num_stops; i++)
	{
		TimeTo *best = new TimeTo;
		int to = requests.at(i);

		get_best_intermediate(
				city,
				s,
				driver,
				to,
				get_constraints(city, driver),
				best->actions,
				best->time_taken);

		if (best->time_taken == sh_time_max || best->actions.size() == 0)
		{
			delete best;
			continue;
		}

		if (best->actions.back() != to)
		{
			std::cout << "Supposed to get us to " << to << std::endl;
			die();
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
		s->service_next(driver, city.get_stop(best->actions.at(i)));
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
