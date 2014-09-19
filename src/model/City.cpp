/*
 * City.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/City.h"
#include "Solution.h"
#include "model/Location.h"

#include "float.h"

#include <fstream>

City::City() : start_action {new Action} { all_actions.push_back(start_action); }
City::~City() {}

int City::get_num_stops() const
{
	return all_actions.size();
}

const Action* City::get_stop(int index) const
{
	return all_actions.at(index);
}

sh_time_t City::get_time_from(location i, location j) const
{
	return all_locations.at(i).get_time_to(all_locations.at(j));
}

void City::add_stop(Action* action)
{
	action->set_index(all_actions.size());
	all_actions.push_back(action);
}

const std::vector<const Action*>& City::get_all_stops() const
{
	return all_actions;
}

int City::get_start_location(int driver) const
{
	return 0;
}

const Location& City::get_location(location l) const
{
	return all_locations.at(l);
}

location City::add_location(const Location& l)
{
	all_locations.push_back(l);
	return all_locations.size() - 1;
}

int City::get_num_trucks() const
{
	return truck_types.size();
}

void City::add_truck(TruckType truck_type)
{
	truck_types.push_back(truck_type);
}

#if 0

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
#endif


void City::loadXml(const tinyxml2::XMLDocument *document)
{
	const tinyxml2::XMLElement* element = document->FirstChildElement("city");
	if (element == nullptr)
	{
		std::cout << "No city found!" << std::endl;
		exit(-1);
	}

	const tinyxml2::XMLElement* actions = element->FirstChildElement("actions")->FirstChildElement("action");
	while (actions != nullptr)
	{
		Action *action = new Action;
		action->loadXml(actions);

		actions = actions->NextSiblingElement();
	}

	const tinyxml2::XMLElement* trucks = element->FirstChildElement("trucks")->FirstChildElement("truck");
	while (trucks != nullptr)
	{
		add_truck(string_to_truck(trucks->Attribute("type")));
		trucks = trucks->NextSiblingElement();
	}

	const tinyxml2::XMLElement* locs = element->FirstChildElement("locations")->FirstChildElement("location");
	while (locs != nullptr)
	{
		Location loc;
		loc.loadXml(locs);
		all_locations.push_back(loc);

		locs = locs->NextSiblingElement();
	}
}

tinyxml2::XMLElement* City::saveXml(tinyxml2::XMLDocument *document) const
{
	tinyxml2::XMLElement* city = document->NewElement("city");

	tinyxml2::XMLElement* actions = document->NewElement("actions");
	std::for_each(all_actions.begin(), all_actions.end(), [&actions](const Action* action)
	{
		action->saveXml(actions);
	});
	city->InsertEndChild(actions);

	tinyxml2::XMLElement* trucks = document->NewElement("trucks");
	std::for_each(truck_types.begin(), truck_types.end(), [&document, &trucks](TruckType type)
	{
		tinyxml2::XMLElement* t = document->NewElement("truck");
		t->SetAttribute("type", truck_to_string(type).c_str());
		trucks->InsertEndChild(t);
	});
	city->InsertEndChild(trucks);

	tinyxml2::XMLElement* locs = document->NewElement("locations");
	for (int i = 0; i < (int) all_locations.size(); i++)
	{
		const Location& loc = all_locations.at(i);
		loc.saveXml(locs)->SetAttribute("idx", i);
	}
	city->InsertEndChild(locs);


	document->InsertEndChild(city);
	return city;
}

int City::get_start_action(int driver) const
{
	return 0;
}

#if 0

void City::refresh_all_actions()
{
	all_actions.clear();

	std::for_each(requests.begin(), requests.end(), [this](const Request& r)
	{
		all_actions.push_back(action_ptr {new Service {&r}});
	});
	std::for_each(land_fills.begin(), land_fills.end(), [this](const Landfill& l)
	{
		all_actions.push_back(action_ptr {new FillLand {l, smallest }});
		all_actions.push_back(action_ptr {new FillLand {l, small    }});
		all_actions.push_back(action_ptr {new FillLand {l, big      }});
		all_actions.push_back(action_ptr {new FillLand {l, biggest  }});
	});
	std::for_each(staging_areas.begin(), staging_areas.end(), [this](const StagingArea &a)
	{
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {Store, smallest, none }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {Store, small,    none }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {Store, big,      none }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {Store, biggest,  none }}});
	});
	std::for_each(staging_areas.begin(), staging_areas.end(), [this](const StagingArea &a)
	{
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {UnStore, none, smallest }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {UnStore, none, small    }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {UnStore, none, big      }}});
		all_actions.push_back(action_ptr{new Action {a, OperationInfo {UnStore, none, biggest  }}});
	});
}


std::ostream& operator<<(std::ostream& os, const City& c)
{
	os << "Requests:" << std::endl;
	os << c.requests.size();
	std::for_each(c.requests.begin(), c.requests.end(), [&os](const Request &r)
	{
		os << r << std::endl;
	});

	os << "Landfills:" << std::endl;
	os << c.land_fills.size();
	std::for_each(c.land_fills.begin(), c.land_fills.end(), [&os](const Landfill &r)
	{
		os << r << std::endl;
	});


	os << "Staging areas:" << std::endl;
	os << c.staging_areas.size();
	std::for_each(c.staging_areas.begin(), c.staging_areas.end(), [&os](const StagingArea &r)
	{
		os << r << std::endl;
	});

	return os;
}
#endif

#if 0
std::ostream& operator>>(std::ostream& os, City& c)
{
	std::string line;
	std::getline(os, line); // Requests:

	int num;
	os >> num;
	for (int i=0; i<num; i++)
	{
		Request r;
		os >> r;
		c.requests.push_back(r);
	}

	std::getline(os, line); // Landfills:
	os >> num;
	for (int i=0; i<num; i++)
	{
		Landfill r;
		os >> r;
		c.land_fills.push_back(r);
	}


	std::getline(os, line); // Staging Areas:
	os >> num;
	for (int i=0; i<num; i++)
	{
		StagingArea r;
		os >> r;
		c.staging_areas.push_back(r);
	}

	return os;
}
#endif

