/*
 * Solution.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include "Solution.h"

#include "model/City.h"

Solution::Solution(int num_drivers)
{
	for (int i = 0; i < num_drivers; i++)
	{
		routes.push_back(new Route);
	}
}

Solution::Solution(const Solution& other)
{
	int size = other.get_num_drivers();
	for (int i = 0; i < size; i++)
	{
		routes.push_back(new Route {other.get_route(i)});
	}
}

Solution& Solution::operator =(const Solution& other)
{
	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		delete routes.at(i);
	}
	routes.clear();

	int size = other.get_num_drivers();
	for (int i = 0; i < size; i++)
	{
		routes.push_back(new Route {other.get_route(i)});
	}

	return *this;
}


Solution::~Solution()
{
	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		delete routes.at(i);
	}
}

sh_time_t Solution::get_time_taken() const
{
	sh_time_t max = 0;

	int num_drivers = get_num_drivers();
	for (int i = 0; i < num_drivers; i++)
	{
		sh_time_t another = routes.at(i)->get_time_taken();
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
		sum += routes.at(i)->get_num_requests_serviced();
	}

	return sum;
}

Route& Solution::get_route(int index) const
{
	return *routes.at(index);
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

	return os;
}

bool Solution::already_serviced(const Request *r) const
{
	if (r == nullptr)
	{
		return false;
	}

	return std::any_of(routes.begin(), routes.end(), [&r](const Route *route) { return route->already_serviced(r); });
}

void Solution::loadXml(const tinyxml2::XMLDocument* document)
{
	std::for_each(routes.begin(), routes.end(), [](const Route* route) { delete route; });
	routes.clear();

	const tinyxml2::XMLElement* solution = document->FirstChildElement("solution");
	if (solution == nullptr)
	{
		std::cout << "No solution found!!!" << std::endl;
	}

	const tinyxml2::XMLElement* routeXml = solution->FirstChildElement("route");
	while (routeXml != nullptr)
	{
		Route* route = new Route;
		route->loadXml(routeXml);
		routes.push_back(route);

		routeXml = routeXml->NextSiblingElement();
	}
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
		routes.at(i)->saveXml(solution)->SetAttribute("num", i);
	}

	document->InsertEndChild(solution);
	return solution;
}

void Solution::validate(const City& city)
{
	// Verify that each request is in the city
}
