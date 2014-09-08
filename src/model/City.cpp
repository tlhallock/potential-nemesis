/*
 * City.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/City.h"
#include "Solution.h"

#include "float.h"

City::City() {}
City::~City() {}

int City::get_num_requests() const
{
	return requests.size();
}

const Landfill& City::get_land_fill(int index) const
{
	return land_fills.at(index);
}

int City::get_num_land_fills() const
{
	return land_fills.size();
}

const Request& City::get_request(int i) const
{
	return requests.at(i);
}

const Landfill& City::get_closest_landfill(const Location& loc) const
{
	double min = DBL_MAX;
	const Landfill* lm = &land_fills.front();

	std::for_each(land_fills.begin(), land_fills.end(), [&min, &loc, &lm](const Landfill &l)
	{
		double a = l.get_time_to(loc);
		if (a >= min)
		{
			return;
		}

		min = a;
		lm = &l;
	});

	return *lm;
}

const std::vector<action_ptr>& City::get_all_actions() const
{
	return all_actions;
}

void City::refresh_all_actions()
{
	all_actions.clear();

	std::for_each(requests.begin(), requests.end(), [this](const Request& r)
	{
		all_actions.push_back(action_ptr {new Request {r}});
	});
	std::for_each(land_fills.begin(), land_fills.end(), [this](const Landfill& l)
	{
		all_actions.push_back(action_ptr {new Action {l, Dump}});
	});
	std::for_each(staging_areas.begin(), staging_areas.end(), [this](const StagingArea &a)
	{
		all_actions.push_back(action_ptr{new Action {a, Store}});
	});
	std::for_each(staging_areas.begin(), staging_areas.end(), [this](const StagingArea &a)
	{
		all_actions.push_back(action_ptr {new Action {a, UnStore}});
	});
}



int City::get_num_staging_areas() const
{
	return staging_areas.size();
}

const StagingArea& City::get_staging_area(int idx) const
{
	return staging_areas.at(idx);
}

std::ostream& operator<<(std::ostream& os, const City& c)
{
	os << "Requests:" << std::endl;
	std::for_each(c.requests.begin(), c.requests.end(), [&os](const Request &r)
	{
		os << r << std::endl;
	});

	os << "Landfills:" << std::endl;
	std::for_each(c.land_fills.begin(), c.land_fills.end(), [&os](const Landfill &r)
	{
		os << r << std::endl;
	});


	os << "Staging areas:" << std::endl;
	std::for_each(c.staging_areas.begin(), c.staging_areas.end(), [&os](const StagingArea &r)
	{
		os << r << std::endl;
	});

	return os;
}


void City::set_requests(std::vector<Request> requests_)
{
	requests = requests_;
	refresh_all_actions();
	std::sort(requests.begin(), requests.end(), [](const Request &r1, const Request &r2)
			{ return r1.get_minimum_time() < r2.get_minimum_time(); });
}

void City::set_land_fills(std::vector<Landfill> land_fills_)
{
	land_fills = land_fills_;
	refresh_all_actions();
}

void City::set_staging_areas(std::vector<StagingArea> staging_areas_)
{
	staging_areas = staging_areas_;
	refresh_all_actions();
}
