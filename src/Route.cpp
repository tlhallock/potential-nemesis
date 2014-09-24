/*
 * Route.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "Route.h"

#include "model/Rules.h"
#include "model/City.h"

#include <algorithm>
#include <iomanip>

Route::Route(const City *city_, int driver_) :
	city{city_},
	driver{driver_}
{
	requests.push_back(city->get_start_action(driver));
}

Route::Route(const Route &other) :
	city{other.city},
	driver{other.driver}
{
	requests.insert(requests.begin(), other.requests.begin(), other.requests.end());
}

Route::~Route() {}

bool Route::can_service_next(const Action* req) const
{
	const Action* last_action = get_last_action();
	return operation_follows(last_action->get_operation(), req->get_operation())
			&& follows_in_time(city, get_time_to_end(), last_action->get_location(), req);
}

void Route::service_next(const Action* req)
{
	requests.push_back(req->get_index());
}

sh_time_t Route::get_time_to_end() const
{
	return get_time_to(requests.size());
}

int Route::get_num_actions() const
{
	return requests.size();
}

const Action* Route::get_action(int index) const
{
	if (index > (int) requests.size())
	{
		std::cout << "trying to get a action that is not in this route!" << std::endl;
		exit(-1);
	}

	return city->get_stop(requests.at(index));
}

const Action* Route::get_last_action() const
{
	int back =  requests.back();
	return city->get_stop(back);
}

void Route::loadXml(const tinyxml2::XMLElement* element)
{
	requests.clear();

	const tinyxml2::XMLElement* stop = element->FirstChildElement("stop");
	while (stop != nullptr)
	{
		int idx;
		stop->QueryIntAttribute("idx", &idx);
		requests.push_back(idx);

		stop = stop->NextSiblingElement("stop");
	}
}

tinyxml2::XMLElement* Route::saveXml(tinyxml2::XMLElement* parent) const
{
	int size = requests.size();

	tinyxml2::XMLElement* route = parent->GetDocument()->NewElement("route");

	route->SetAttribute("driver", driver);

	for (int i = 0; i < size; i++)
	{
		tinyxml2::XMLElement* stop = parent->GetDocument()->NewElement("stop");
		stop->SetAttribute("idx", requests.at(i));
		route->InsertEndChild(stop);
	}

	parent->InsertEndChild(route);
	return route;
}

const City* Route::get_city() const
{
	return city;
}

sh_time_t Route::get_time_to(const int max) const
{
	int location = city->get_start_location(driver);
	sh_time_t end_time = 0;
	for (int i = 0; i < max; i++)
	{
		const Action* current = city->get_stop(requests.at(i));
		end_time += get_time_taken(city, end_time, location, current);
		location = current->get_location();
	}
	return end_time;
}


int Route::get_num_requests_serviced() const
{
	int sum = 0;
	for (unsigned int i = 0; i < requests.size(); i++)
	{
		sum += get_points(city->get_stop(requests.at(i))->get_operation());
	}
	return sum;
}

std::ostream& operator<<(std::ostream& os, const Route& r)
{
	os << "\tRoute: t=" << r.get_time_to_end() << " n=" << r.get_num_requests_serviced() << " path=" << std::endl;
	for (unsigned int i = 0; i < r.requests.size(); i++)
	{
		const Action* action = r.city->get_stop(r.requests.at(i));

		sh_time_t ctime = r.get_time_to(i + 1);
		sh_time_t otime = r.get_time_to(i);

		os << "\t\t[" << std::setw(4) << i << " t=" << std::setw(5) << ctime;
		if (i != 0)
		{
			os << " d=" << std::setw(5) << (ctime - otime);
		}
		else
		{
			os << "        ";
		}
		os << " : " << *action << "]" << std::endl;
	}
	return os;
}
