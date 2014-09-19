/*
 * Action.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Action.h"

#include <climits>
#include <iomanip>


Action::~Action() {}



const Action* get_start_action()
{
	return new Action;
}

int Action::get_points() const
{
	switch(get_operation())
	{
		case Replace  :
			return 2;
		case PickUp   :
		case DropOff  :
		case Dump     :
			return 1;
		case Store    :
		case UnStore  :
			return 0;
	}
}

std::ostream& operator<<(std::ostream& os, const Action& a)
{
	return os << Location {a} << OperationInfo {a} << std::endl;
}


bool satisfies_operation_constraint(action_ptr action, const operation_location_constraint& constraint)
{
	auto it = constraint.find(action->get_operation());
	if (it == constraint.end())
	{
		return true;
	}

	const Location& loc = it->second;
	return action->get_x() == loc.get_x()
			&& action->get_y() == loc.get_y();
}


void Action::loadXml(const tinyxml2::XMLElement* action)
{
	Location::loadXml(action);
	OperationInfo::loadXml(action);
}

int Action::get_index()
{
	return index;
}

void Action::set_index(int ndx)
{
	index = ndx;
}

location Action::get_location()
{
	return  loc;
}

sh_time_t Action::get_minimum_time() const
{
	return min_time;
}

sh_time_t Action::get_maximum_time() const
{
	return max_time;
}

sh_time_t Action::get_wait_time() const
{
	return time_required;
}

tinyxml2::XMLElement* Action::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* action = parent->GetDocument()->NewElement("action");
	Location::saveXml(action);
	OperationInfo::saveXml(action);
	parent->InsertEndChild(action);
	return action;
}

Action::Action() : Action {Store, none, none, 0, sh_time_look_ahead, 0, INT_MAX, {0, 0, 0, 0}, 0} {}

Action::Action(
		Operation o_,
		DumpsterSize insize_,
		DumpsterSize outsize_,
		sh_time_t min,
		sh_time_t max,
		sh_time_t time,
		uint32_t max_dumpsters_,
		uint32_t initial_inventory_[],
		int location_) :
	o{o_},
	insize{insize_},
	outsize{outsize_},
	min_time {min},
	max_time{max},
	time_required{time},
	max_dumpsters{max_dumpsters_},
	//initial_inventory[4];
	loc{location_},
	index{0}
{
	for(int i=0;i<4;i++)
	{
		initial_inventory[i] = initial_inventory_[i];
	}
}

DumpsterSize Action::get_output_dumpster_size() const
{
	return outsize;
}

DumpsterSize Action::get_input_dumpster_size() const
{
	return insize;
}

Operation Action::get_operation() const
{
	return o;
}


#if 0

xml's


void StagingArea::loadXml(const tinyxml2::XMLElement* area)
{
	Location::loadXml(area);

	const tinyxml2::XMLElement* wait = area->FirstChildElement("wait");
	if (wait == nullptr)
	{
		std::cout << "While parsing staging area: no wait time." << std::endl;
	}
	else
	{
		wait->QueryUnsignedAttribute("time", &wait_time);
	}

	const tinyxml2::XMLElement* containers = area->FirstChildElement("containers");
	if (containers == nullptr)
	{
		std::cout << "While parsing staging area: no wait time." << std::endl;
	}
	else
	{
		containers->QueryUnsignedAttribute("max", &max_containers);
	}
}

tinyxml2::XMLElement* StagingArea::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* area = parent->GetDocument()->NewElement("stagingarea");

	Location::saveXml(area);
	tinyxml2::XMLElement* wait = parent->GetDocument()->NewElement("wait");
	wait->SetAttribute("time", wait_time);
	area->InsertEndChild(wait);
	tinyxml2::XMLElement* containers = parent->GetDocument()->NewElement("containers");
	containers->SetAttribute("max", max_containers);
	area->InsertEndChild(containers);

	parent->InsertEndChild(area);
	return area;
}
void OperationInfo::loadXml(const tinyxml2::XMLElement* element)
{
	const char *op = element->Attribute("operation");
	if (op == nullptr)
	{
		std::cout << "No operation for OperationInfo!!!!" << std::endl;
		exit(-1);
	}
	o = char_to_operation(*op);
	insize = string_to_size(element->Attribute("in"));
	outsize = string_to_size(element->Attribute("out"));
}

tinyxml2::XMLElement* OperationInfo::saveXml(tinyxml2::XMLElement* parent) const
{
	parent->SetAttribute("operation", operation_to_svg(o).c_str());
	parent->SetAttribute("in", size_to_string(insize).c_str());
	parent->SetAttribute("out", size_to_string(outsize).c_str());
	return parent;
}


void Request::loadXml(const tinyxml2::XMLElement* element)
{
	Location::loadXml(element);
	OperationInfo::loadXml(element);
	const tinyxml2::XMLElement* window = element->FirstChildElement("window");
	if (window == nullptr)
	{
		start_time = 0;
		stop_time = sh_time_max;
	}
	else
	{
		window->QueryUnsignedAttribute("begin", &start_time);
		window->QueryUnsignedAttribute("end", &stop_time);
	}
}

tinyxml2::XMLElement* Request::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* request = parent->GetDocument()->NewElement("request");

	Location::saveXml(request);
	OperationInfo::saveXml(request);

	tinyxml2::XMLElement* window = parent->GetDocument()->NewElement("window");
	window->SetAttribute("begin", start_time);
	window->SetAttribute("end", stop_time);
	request->InsertEndChild(window);

	parent->InsertEndChild(request);
	return request;
}


bool Service::follows_in_time(sh_time_t start_time, const Location& from) const
{
	sh_time_t time_taken = get_time_taken(start_time, from);
	return
	#if CANT_HIT_TOO_EARLY
			time_taken > req->get_minimum_time() &&
	#endif
			time_taken < req->get_maximum_time();
}

#endif
