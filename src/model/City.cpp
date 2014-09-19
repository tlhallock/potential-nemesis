/*
 * City.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/City.h"
#include "Solution.h"
#include "model/FillLand.h"
#include "model/Service.h"

#include "float.h"

#include <fstream>

City::City() {}
City::~City() {}

int City::get_num_stops() const
{
	return all_actions.size();
}

const Action* City::get_stop(int index) const
{
	return all_actions.at(index);
}

sh_time_t City::get_time_from(int i, int j)
{
	return 0.0;
}

void City::add_stop(Action* action)
{
	all_actions.push_back(action);
}

const std::vector<const Action*>& City::get_all_stops() const
{
	return all_actions;
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

#if 0

void City::loadXml(const tinyxml2::XMLDocument *document)
{
	const tinyxml2::XMLElement* element = document->FirstChildElement("city");
	if (element == nullptr)
	{
		std::cout << "No city found!" << std::endl;
		exit(-1);
	}

	const tinyxml2::XMLElement* list = element->FirstChildElement();
	while (list != nullptr)
	{
		const char* name = list->Name();
		if (strcmp(name, "landfills") == 0)
		{
			const tinyxml2::XMLElement* landfill_list = list->FirstChildElement();
			while (landfill_list != nullptr)
			{
				Landfill l;
				l.loadXml(landfill_list);
				landfill_list = landfill_list->NextSiblingElement();
				land_fills.push_back(l);
			}
		}
		else if (strcmp(name, "stagingareas") == 0)
		{
			const tinyxml2::XMLElement* landfill_list = list->FirstChildElement();
			while (landfill_list != nullptr)
			{
				StagingArea l;
				l.loadXml(landfill_list);
				landfill_list = landfill_list->NextSiblingElement();
				staging_areas.push_back(l);
			}
		}
		else if (strcmp(name, "requests") == 0)
		{
			const tinyxml2::XMLElement* requestList = list->FirstChildElement();
			while (requestList != nullptr)
			{
				Request r;
				r.loadXml(requestList);
				requestList = requestList->NextSiblingElement();
				requests.push_back(r);
			}
		}
		else
		{
			std::cout << "Unknown element name: " << name <<"." << std::endl;
			std::cout << "Goodbye cruel world!" << std::endl;
			exit(-1);
		}

		list = list->NextSiblingElement();
	}
}

tinyxml2::XMLElement* City::saveXml(tinyxml2::XMLDocument *document) const
{
	tinyxml2::XMLElement* city = document->NewElement("city");

	tinyxml2::XMLElement* requestlist = document->NewElement("requests");
	city->InsertEndChild(requestlist);
	requestlist->SetAttribute("len", (int) requests.size());
	std::for_each(requests.begin(), requests.end(), [requestlist](const Request &r)
	{
		r.saveXml(requestlist);
	});


	tinyxml2::XMLElement* landfills = document->NewElement("landfills");
	city->InsertEndChild(landfills);
	landfills->SetAttribute("len", (int) land_fills.size());
	std::for_each(land_fills.begin(), land_fills.end(), [landfills](const Landfill &r)
	{
		r.saveXml(landfills);
	});

	tinyxml2::XMLElement* stagingareas = document->NewElement("stagingareas");
	city->InsertEndChild(stagingareas);
	stagingareas->SetAttribute("len", (int) staging_areas.size());
	std::for_each(staging_areas.begin(), staging_areas.end(), [stagingareas](const StagingArea &r)
	{
		r.saveXml(stagingareas);
	});
	document->InsertEndChild(city);
	return city;
}


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

