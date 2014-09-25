/*
 * Solution.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Solution.h"

#include "model/Rules.h"

#include <algorithm>
#include <iomanip>

Solution::Solution(const City *city_) :
	city(city_),
	m_already_serviced{(bool *)calloc(city->get_num_stops(), sizeof(*m_already_serviced))}
{
	int num_drivers = city->get_num_trucks();
	for (int i = 0; i < num_drivers; i++)
	{
		routes.push_back(Route {city, i});
	}

	set_yards(city->get_staging_areas());
}

Solution::Solution(const Solution& other) :
			city(other.city),
			m_already_serviced{(bool *)calloc(city->get_num_stops(), sizeof(*m_already_serviced))}
{
	int size = other.get_num_drivers();
	for (int i = 0; i < size; i++)
	{
		routes.push_back(Route {other.get_route(i)});
	}

	yards = other.yards;
}

Solution& Solution::operator =(const Solution& other)
{
	if (city->get_num_stops() != other.city->get_num_stops())
	{
		puts("Assigning solution to different city!!!");
		die();
	}
	city = other.city;

	int num_stops = city->get_num_stops();

	for (int i = 0; i < num_stops; i++)
	{
		m_already_serviced[i] = other.m_already_serviced[i];
	}

	routes.clear();
	int size = other.get_num_drivers();
	for (int i = 0; i < size; i++)
	{
		routes.push_back(Route {other.get_route(i)});
	}

	yards = other.yards;

	return *this;
}


Solution::~Solution()
{
	free(m_already_serviced);
}

sh_time_t Solution::get_time_taken() const
{
	sh_time_t max = 0;

	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		sh_time_t another = routes.at(i).get_time_to_end();
		if (another > max)
		{
			max = another;
		}
	}

	return max;
}

int Solution::get_num_requests_serviced() const
{
	sh_time_t sum = 0;

	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		sum += routes.at(i).get_num_requests_serviced();
	}

	return sum;
}

const Route& Solution::get_route(int index) const
{
	return routes.at(index);
}

Route& Solution::get_route(int index)
{
	if (index > (int) routes.size())
	{
		std::cout << "Trying to get a route that doesn't exist!" << std::endl;
		die();
	}

	return routes.at(index);
}

int Solution::get_num_drivers() const
{
	return routes.size();
}

std::ostream& operator<<(std::ostream& os, const Solution& r)
{
	int num_drivers = r.get_num_drivers();
	os << "Num drivers: " << r.get_num_drivers() << " t=" << r.get_time_taken() << " n=" << r.get_num_requests_serviced() << std::endl;

	for (int i = 0; i < num_drivers; i++)
	{
		os << "Route [" << i << "]:\n" << r.get_route(i);
	}

	auto end = r.yards.end();
	for (auto it = r.yards.begin(); it != end; ++it)
	{
		os << std::setw(5) << it->first << ": " << it->second << std::endl;
	}

	return os;
}

bool Solution::already_serviced(const Action *r) const
{
	return             r->get_operation() != Dump
			&& r->get_operation() != Store
			&& r->get_operation() != UnStore
			&& m_already_serviced[r->get_index()];
}

void Solution::loadXml(const tinyxml2::XMLDocument* document)
{
	routes.clear();

	const tinyxml2::XMLElement* solution = document->FirstChildElement("solution");
	if (solution == nullptr)
	{
		std::cout << "No solution found!!!" << std::endl;
		die();
	}

	const tinyxml2::XMLElement* routeXml = solution->FirstChildElement("route");
	while (routeXml != nullptr)
	{
		routes.push_back(Route {city, (int) routes.size()});
		routes.back().loadXml(routeXml);

		routeXml = routeXml->NextSiblingElement();
	}

	std::cout << "Still need to set already serviced and the yards..." << std::endl;
}

tinyxml2::XMLElement*  Solution::saveXml(tinyxml2::XMLDocument* document) const
{
	tinyxml2::XMLElement* solution = document->NewElement("solution");

	tinyxml2::XMLElement* stats = document->NewElement("stats");
	stats->SetAttribute("drivers", get_num_drivers());
	stats->SetAttribute("time", get_time_taken());
	stats->SetAttribute("handled", get_num_requests_serviced());
	solution->InsertEndChild(stats);

	int size = routes.size();
	for (int i = 0; i < size; i++)
	{
		routes.at(i).saveXml(solution);
	}

	document->InsertEndChild(solution);
	return solution;
}

bool Solution::service_next(int driver, const Action* action)
{
	sh_time_t end_time;
	if (!is_possible(city, this, driver, action, end_time, true))
	{
		std::cout << "Impossible state:\n" << *action << " from driver " << driver << " in \n" << *this << std::endl;
		die();
		return false;
	}
	routes.at(driver).service_next(action);
	m_already_serviced[action->get_index()] = true;

//	auto it = yards.find(action->get_location());
//	if (it != yards.end())
//	{
//		it->second.applied(action);
//	}

	return true;
}

void Solution::validate()
{
	if (city->get_num_trucks() != (int) routes.size())
	{
		std::cout << "Not the right number of trucks!" << std::endl;
	}

	int num_actions = city->get_num_stops();

	Solution tst {city};
	for (int route = 0; route < (int) routes.size(); route++)
	{
		Route& r = routes.at(route);

		// starting at 1 to skip the start location...
		for (int stop = 1; stop < r.get_num_actions(); stop++)
		{
			int ndx = r.requests.at(stop);
			if (ndx < 0 || ndx >= num_actions)
			{
				std::cout << "Invalid index at route " << route << " stop " << stop << " ndx = " << ndx << std::endl;
				die();
			}
			tst.service_next(route, city->get_stop(ndx));
		}
	}

	std::cout << "The city is good!" << std::endl;
}

void Solution::set_yards(const std::map<const int, const StagingArea> other)
{
	yards.clear();
	auto end = other.end();
	for (auto it = other.begin(); it != end; ++it)
	{
		yards.insert(std::pair<int, StagingArea> { it->first, StagingArea{it->second} });
	}
}
