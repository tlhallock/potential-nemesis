/*
 * Route.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "Route.h"

#include "model/Landfills.h"

#include <algorithm>
#include <iomanip>

Route::Route()
{
	requests.push_back(new Action(get_start_action()));
}

Route::~Route()
{
	std::for_each(requests.begin(), requests.end(), [](const Action *a)
	{
		delete a;
	});
}

bool Route::can_service_next(const Action &req) const
{
	sh_time_t time_taken = req.get_time_taken(get_time_taken(), *requests.back());
	return requests.back()->follows(req)
//			&& time_taken > req.get_minimum_time()
			&& time_taken < req.get_maximum_time();
}

void Route::service_next(const Action *req)
{
	if (!can_service_next(*req))
	{
		std::cout << "Impossible state: " << *req << " from\n" << *this << std::endl;
		return;
	}

	requests.push_back(req);
}

sh_time_t Route::get_time_taken() const
{
	return get_time_taken(requests.size());
}

TruckState Route::get_truck_state() const
{
	return requests.back()->get_truck_state();
}

std::vector<Action> Route::get_next_possibles() const
{
	std::vector<Action> actions;

	const Action *a = requests.back();
	switch (a->get_truck_state())
	{
	case EmptyDumpster:
		if (a->get_operation() != UnStage)
		{
			actions.push_back(Action{get_closest_landfill(*a), Stage});
		}
		break;
	case FullDumpster:
		actions.push_back(Action{get_closest_landfill(*a), Dump});
		break;
	case NoDumpster:
		if (a->get_operation() != Stage)
		{
			actions.push_back(Action{get_closest_landfill(*a), UnStage});
		}
		break;
	default:
		std::cout << "Do not go here 13094109843" << std::endl;
		break;
	}
	return actions;
}


int Route::get_num_actions() const
{
	return requests.size();
}

const Action& Route::get_action(int index) const
{
	return *requests.at(index);
}

sh_time_t Route::get_time_taken(const int max) const
{
	if (max <= 1)
	{
		return 0;
	}

	const Action *a1 = requests.at(max - 1);
	const Action *a2 = requests.at(max - 2);

	return a1->get_time_taken(get_time_taken(max - 1), *a2);
}


int Route::get_num_requests_serviced() const
{
	int sum = 0;
	for (unsigned int i = 0; i < requests.size(); i++)
	{
		sum += requests.at(i)->get_points();
	}
	return sum;
}

std::ostream& operator<<(std::ostream& os, const Route& r)
{
	os << "\tRoute: t=" << r.get_time_taken() << " n=" << r.get_num_requests_serviced() << " path=" << std::endl;
	for (unsigned int i = 0; i < r.requests.size(); i++)
	{
		const Action *a = r.requests.at(i);

		os << "\t\t[" << std::setw(4) << i
				<< " t=" << std::setw(5) << r.get_time_taken(i + 1);
		if (i != 0)
		{
				os << " d=" << std::setw(5) << (r.requests.at(i-1)->get_time_to(*a));
		}
		os << " : " << *a << "]" << std::endl;
	}
	return os;
}
