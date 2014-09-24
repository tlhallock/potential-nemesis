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
	return 0;
}

std::ostream& operator<<(std::ostream& os, const Action& a)
{
	return os       << " [op=" << std::setw(10) << operation_to_string(a.o)
			<< "][in=" << std::setw(10) << size_to_string(a.insize)
			<< "][out=" << std::setw(10) << size_to_string(a.outsize)
			<< "][min=" << std::setw(5) << a.min_time
			<< "][max=" << std::setw(5) << a.max_time
			<< "][wait=" << std::setw(5) << a.time_required
//			<< "][max=" << std::setw(10) << a.max_dumpsters
			<< "][loc=" << std::setw(5) << a.loc << "]"
			<< "][idx=" << std::setw(5) << a.index << "]"
			;
}


void Action::loadXml(const tinyxml2::XMLElement* action)
{
	loc = -1;
	action->QueryIntAttribute("loc", (int*) &loc);
	if (loc < 0)
	{
		std::cout << "Error while loading action: no location!" << std::endl;
		exit(-1);
	}

	const tinyxml2::XMLElement* wait = action->FirstChildElement("wait");
	if (wait == nullptr)
	{
		std::cout << "While parsing staging area: no wait time." << std::endl;
	}
	else
	{
		wait->QueryUnsignedAttribute("time", &time_required);
	}



	const char *op = action->Attribute("operation");
	if (op == nullptr)
	{
		std::cout << "No operation for OperationInfo!!!!" << std::endl;
		exit(-1);
	}
	o = char_to_operation(*op);
	insize = string_to_size(action->Attribute("in"));
	outsize = string_to_size(action->Attribute("out"));


	const tinyxml2::XMLElement* window = action->FirstChildElement("window");
	if (window == nullptr)
	{
		min_time = 0;
		max_time = sh_time_max;
	}
	else
	{
		window->QueryUnsignedAttribute("begin", &min_time);
		window->QueryUnsignedAttribute("end", &max_time);
	}
}

tinyxml2::XMLElement* Action::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* action = parent->GetDocument()->NewElement("action");

	action->SetAttribute("loc", loc);
	tinyxml2::XMLElement* wait = parent->GetDocument()->NewElement("wait");
	wait->SetAttribute("time", time_required);
	action->InsertEndChild(wait);

	action->SetAttribute("operation", operation_to_svg(o).c_str());
	action->SetAttribute("in", size_to_string(insize).c_str());
	action->SetAttribute("out", size_to_string(outsize).c_str());

	tinyxml2::XMLElement* window = parent->GetDocument()->NewElement("window");
	window->SetAttribute("begin", min_time);
	window->SetAttribute("end", max_time);
	action->InsertEndChild(window);

	parent->InsertEndChild(action);
	return action;
}

int Action::get_index() const
{
	return index;
}

void Action::set_index(int ndx)
{
	index = ndx;
}

location Action::get_location() const
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


int *initial_inventory = (int *) calloc (sizeof(*initial_inventory), 4);
Action::Action() : Action {Store, none, none, 0, sh_time_look_ahead, 0, 0} {}

Action::Action(
		Operation o_,
		DumpsterSize insize_,
		DumpsterSize outsize_,
		sh_time_t min,
		sh_time_t max,
		sh_time_t time,
		location location_) :
	o{o_},
	insize{insize_},
	outsize{outsize_},
	min_time {min},
	max_time{max},
	time_required{time},
	loc{location_},
	index{0} {}

std::ostream &Action::save_to_matlab(std::ostream& out) const
{
	out << "stops(" << index << ") = struct( ";
	out << "\"operation\", '" << operation_to_svg(o) << "', ";
	out << "\"in_size\", '" << get_size_text(insize) << "', ";
	out << "\"out_size\", '" << get_size_text(outsize) << "', ";
	out << "\"min_time\", " << min_time << ", ";
	out << "\"max_time\", " << max_time << ", ";
	out << "\"time_required\", " << time_required << ", ";

	out << "\"location\", " << loc;

	out << ");" << std::endl;

	return out;
}
