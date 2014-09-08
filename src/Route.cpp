/*
 * Route.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "Route.h"

#include "model/Landfills.h"
#include "model/Rules.h"

#include <algorithm>
#include <iomanip>

Route::Route()
{
	requests.push_back(get_start_action());
}

Route::~Route() {}

bool Route::can_service_next(action_ptr req) const
{
	return operation_follows(requests.back()->get_operation(), req->get_operation())
			&& req->follows_in_time(get_time_taken(), *requests.back().get());
}

void Route::service_next(action_ptr req)
{
	if (!can_service_next(req))
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

int Route::get_num_actions() const
{
	return requests.size();
}

const Action& Route::get_action(int index) const
{
	return *requests.at(index);
}

const Location& Route::get_current_location() const
{
	return *requests.back();
}

const Action& Route::get_last_action() const
{
	return get_action(requests.size() - 1);
}

sh_time_t Route::get_time_taken(const int max) const
{
	if (max <= 1)
	{
		return 0;
	}

	const action_ptr &a1 = requests.at(max - 1);
	const action_ptr &a2 = requests.at(max - 2);

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
		const action_ptr &a = r.requests.at(i);

		os << "\t\t[" << std::setw(4) << i
				<< " t=" << std::setw(5) << r.get_time_taken(i + 1);
		if (i != 0)
		{
				os << " d=" << std::setw(5) << (r.requests.at(i-1)->get_time_to(*a.get()));
		}
		os << " : " << *a << "]" << std::endl;
	}
	return os;
}

bool Route::already_serviced(const action_ptr& r) const
{
	return std::any_of(requests.begin(), requests.end(), [&r](const action_ptr &a){ return a->satisfies(r); });
}
