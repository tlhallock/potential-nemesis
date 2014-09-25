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

namespace
{
	IntermediateAction empty_intermediate{-13};
}

City::City() :
	start_action {new Action},
	distances{(double *) malloc (sizeof (*distances))},
	intermediate_actions{nullptr}
{
	add_location(Location{});
	start_action->set_index(START_INDEX);
}
City::~City()
{
	free(distances);
	free(intermediate_actions);
}

int City::get_num_stops() const
{
	return all_actions.size();
}

const Action* City::get_stop(int index) const
{
	if (index == START_INDEX)
	{
		return start_action;
	}

	return all_actions.at(index);
}

sh_time_t City::get_time_from(location i, location j) const
{
	return distances[i * all_locations.size() + j];
}

std::ostream& City::save_to_matlab(std::ostream& out) const
{
	for_each(all_actions.begin(), all_actions.end(), [&out](const Action *a){ a->save_to_matlab(out); });
	return out;
}

void City::refresh_distances()
{
	free(distances);

	int num = all_locations.size();
	distances = (double *) malloc(sizeof(*distances) * num * num);

	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < num; j++)
		{
			distances[i * num + j] = all_locations.at(i).get_time_to(all_locations.at(j));
		}
	}
}

const std::map<const int, const StagingArea>& City::get_staging_areas() const
{
	return staging_areas;
}

void City::refresh_intermediates() const
{
	if (intermediate_actions != nullptr)
	{
		return;
	}

	int size = all_actions.size();
	intermediate_actions = (IntermediateAction **) calloc (size * size, sizeof (*intermediate_actions));

	request_indices.clear();

	Operation o;

	std::cout << "Creating intermediates..." << std::endl;
	int total_paths = 0;

	for (int i=0; i<size; i++)
	{
		o = all_actions.at(i)->get_operation();
		if (o == Store || o == UnStore || o == Dump)
		{
			continue;
		}
		request_indices.push_back(i);

		for (int j=0;j<size;j++)
		{
			if (i == j)
			{
				continue;
			}
			o = all_actions.at(j)->get_operation();
			if (o == Store || o == UnStore || o == Dump)
			{
				continue;
			}

			IntermediateAction *inter = create_intermediate_action(all_actions, i, j);

			total_paths += inter->get_num_paths();
			intermediate_actions[i * size + j] = inter;
		}
	}

	std::cout << "Done. # intermediates = " << total_paths << std::endl;
}

const std::vector<int>& City::get_requests() const
{
	refresh_intermediates();

#if 0
	for (auto it = request_indices.begin(); it != request_indices.end(); ++it)
	{
		int to = *it;
		if (get_stop(to)->get_operation() == Store
				|| get_stop(to)->get_operation() == UnStore
				|| get_stop(to)->get_operation() == Dump)
		{
			std::cout << "Error" << get_stop(to)->get_operation() << std::endl;
			die();
		}
	}
#endif

	return request_indices;
}

const IntermediateAction* City::get_intermediates(int i, int j) const
{
	refresh_intermediates();
	return intermediate_actions[i * all_actions.size() + j];
}

void City::clear_intermediates() const
{
	if (intermediate_actions == nullptr)
	{
		return;
	}
	int num = all_actions.size();
	for (int i=0; i<num * num;i++)
	{
		delete intermediate_actions[i];
	}
	free(intermediate_actions);
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

const Action* City::get_start_action(int driver) const
{
	return start_action;
}

void City::add_staging_area(Location loc, int* inventories, int capacity)
{
	clear_intermediates();

	DumpsterSize sizes[] = {smallest, small, big, biggest};
	location l = add_location(loc);
	for (int j = 0; j < 4; j++)
	{
		add_stop(new Action
		{
			Store,
			sizes[j],
			none,
			0,
			sh_time_look_ahead,
			STAGE_TIME,
			l
		});
		add_stop(new Action
		{
			UnStore,
			none,
			sizes[j],
			0,
			sh_time_look_ahead,
			STAGE_TIME,
			l
		});
	}

	staging_areas.insert(std::pair<int, StagingArea>{l, StagingArea{l, capacity, inventories}});
}

void City::add_land_fill(Location loc)
{
	clear_intermediates();

	DumpsterSize sizes[] = {smallest, small, big, biggest};
	location l = add_location(loc);
	for (int j = 0; j < 4; j++)
	{
		add_stop(new Action
		{
			Dump,
			sizes[j],
			sizes[j],
			0,
			sh_time_look_ahead,
			LANDFILL_TIME,
			l
		});
	}
}

void City::add_request(Action* action)
{
	clear_intermediates();

	add_stop(action);
}

const Location& City::get_location(location l) const
{
	return all_locations.at(l);
}

location City::add_location(const Location& l)
{
	for (int i = 0; i < (int) all_locations.size(); i++)
	{
		if (all_locations.at(i) == l)
		{
			return i;
		}
	}

	all_locations.push_back(l);
	refresh_distances();
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
		die();
	}

	std::for_each(all_actions.begin(), all_actions.end(), [](const Action* action) { delete action; });

	clear_intermediates();

	all_actions.clear();
	all_locations.clear();
	truck_types.clear();
	staging_areas.clear();

	int ndx=0;
	const tinyxml2::XMLElement* actions = element->FirstChildElement("actions")->FirstChildElement("action");
	while (actions != nullptr)
	{
		Action *action = new Action;
		action->loadXml(actions);
		action->set_index(ndx++);
		all_actions.push_back(action);

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


	const tinyxml2::XMLElement* yards = element->FirstChildElement("yards")->FirstChildElement("yard");
	while (yards != nullptr)
	{
		StagingArea a;
		a.loadXml(yards);
		staging_areas.insert(std::pair<int, StagingArea> {a.get_location(), a});

		yards = yards->NextSiblingElement();
	}

	refresh_distances();
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


	tinyxml2::XMLElement* yards = document->NewElement("yards");

	auto end = staging_areas.end();
	for (auto it = staging_areas.begin(); it != end; ++it)
	{
		it->second.saveXml(yards);
	}
	city->InsertEndChild(yards);


	document->InsertEndChild(city);
	return city;
}

IntermediateAction::IntermediateAction(int dest_) : dest{dest_} {}
IntermediateAction::~IntermediateAction() {}

void IntermediateAction::add_alternative(const std::vector<int>& path)
{
	if (path.back() != dest)
	{
		std::cout << "This is supposed to get us there!" << std::endl;
		die();
	}
	alternatives.push_back(path);
}

IntermediateAction *create_intermediate_action(const std::vector<const Action*>& all, int from, int to)
{
	IntermediateAction *ret_val = new IntermediateAction {to};

	Operation prevO = all.at(from)->get_operation();
	Operation nextO = all.at(to)->get_operation();

	DumpsterSize prevS = all.at(from)->get_output_dumpster_size();
	DumpsterSize nextS = all.at(to)->get_input_dumpster_size();

	if (prevO == PickUp || prevO == Replace)
	{
		if (nextO == PickUp)
		{
			// dump -> stage -> to
			auto end = all.end();
			for (auto it = all.begin(); it != end; ++it)
			{
				const Action* action = *it;
				if (action->get_operation() != Dump)
				{
					continue;
				}

				if (action->get_input_dumpster_size() != prevS)
				{
					continue;
				}

				auto iend = all.end();
				for (auto iit = all.begin(); iit != iend; ++iit)
				{
					const Action* action2 = *iit;
					if (action2->get_operation() != Store)
					{
						continue;
					}
					if (action2->get_input_dumpster_size() != prevS)
					{
						continue;
					}

					std::vector<int> alt;
					alt.push_back(action->get_index());
					alt.push_back(action2->get_index());
					alt.push_back(to);
					ret_val->add_alternative(alt);
				}
			}
		}
		else if (nextO == DropOff || nextO == Replace)
		{
			if (prevS == nextS)
			{
				// dump
				auto end = all.end();
				for (auto it = all.begin(); it != end; ++it)
				{
					const Action* action = *it;
					if (action->get_operation() != Dump)
					{
						continue;
					}
					if (action->get_output_dumpster_size() != nextS)
					{
						continue;
					}

					std::vector<int> alt;
					alt.push_back(action->get_index());
					alt.push_back(to);
					ret_val->add_alternative(alt);
				}
			}
			else
			{
				// dump -> stage -> unstage
				auto end = all.end();
				for (auto it = all.begin(); it != end; ++it)
				{
					const Action* action = *it;
					if (action->get_operation() != Dump)
					{
						continue;
					}

					if (action->get_input_dumpster_size() != prevS)
					{
						continue;
					}

					auto iend = all.end();
					for (auto iit = all.begin(); iit != iend; ++iit)
					{
						const Action* action2 = *iit;
						if (action2->get_operation() != Store)
						{
							continue;
						}
						if (action2->get_input_dumpster_size() != prevS)
						{
							continue;
						}

						auto iiend = all.end();
						for (auto iiit = all.begin(); iiit != iiend; ++iiit)
						{
							const Action* action3 = *iiit;
							if (action3->get_operation() != UnStore)
							{
								continue;
							}
							if (action3->get_output_dumpster_size() != nextS)
							{
								continue;
							}

							std::vector<int> alt;
							alt.push_back(action->get_index());
							alt.push_back(action2->get_index());
							alt.push_back(action3->get_index());
							alt.push_back(to);
							ret_val->add_alternative(alt);
						}
					}
				}
			}
		}
	}
	else if (prevO == DropOff)
	{
		if (nextO == PickUp)
		{
			// to
			std::vector<int> alt;
			alt.push_back(to);
			ret_val->add_alternative(alt);
		}
		else if (nextO == DropOff || nextO == Replace)
		{
			// unstore -> to
			auto end = all.end();
			for (auto it = all.begin(); it != end; ++it)
			{
				const Action* action = *it;
				if (action->get_operation() != UnStore)
				{
					continue;
				}
				if (action->get_input_dumpster_size() != prevS)
				{
					continue;
				}

				std::vector<int> alt;
				alt.push_back(action->get_index());
				alt.push_back(to);
				ret_val->add_alternative(alt);
			}
		}
	}

	return ret_val;
}

std::ostream& operator<<(std::ostream& os, const IntermediateAction& action)
{
	auto end = action.alternatives.end();
	for (auto it = action.alternatives.begin(); it != end; ++it)
	{
		auto iend = it->end();
		for (auto iit = it->begin(); iit != iend; ++iit)
		{
			os << *iit << " ";
		}
		os << std::endl;
	}
	os << "\n\n\n\n\n" << std::endl;

	return os;
}

int IntermediateAction::get_num_paths() const
{
	return alternatives.size();
}

const std::vector<std::vector<int> >& IntermediateAction::get_alternatives() const
{
	return alternatives;
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

