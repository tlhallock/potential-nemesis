/*
 * Action.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Action.h"

#include <climits>
#include <iomanip>


Action::Action() : Action {Location{} , Store, none, none} {}
Action::Action(const Location& l_, const Operation& o_, DumpsterSize in, DumpsterSize out) :
	Location(l_),
	OperationInfo {o, in, out} {}

Action::~Action() {}

sh_time_t Action::get_time_taken(sh_time_t start_time, const Location& from) const
{
	return start_time + from.get_time_to(*this);
}

bool Action::follows_in_time(sh_time_t start_time, const Location& from) const
{
	return 0;
#if CANT_HIT_TOO_EARLY

	// Until i figure out where the follows in time method goes

	sh_time_t time_taken = get_time_taken(start_time, from);
	return
			time_taken > get_minimum_time() &&
			time_taken < get_maximum_time();
#endif
}

action_ptr get_start_action()
{
	return action_ptr {new Action{Location{0, 0}, Store, none, none}};
}

int Action::get_points() const { return 0; }

std::ostream& operator<<(std::ostream& os, const Action& a)
{
	return os << Location {a} << OperationInfo {a} << std::endl;
}

bool Action::satisfies(const Request *request) const
{
	return false;
}

bool satisfies_operation_constraint(const action_ptr &action, const operation_location_constraint& constraint)
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
	const char *op = action->Attribute("operation");
	if (op == nullptr)
	{
		std::cout << "No operation for action!!!!" << std::endl;
		exit(-1);
	}
	o = char_to_operation(*op);

	insize = string_to_size(action->Attribute("in"));
	outsize = string_to_size(action->Attribute("out"));

	Location::loadXml(action);
}

tinyxml2::XMLElement* Action::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* action = parent->GetDocument()->NewElement("action");
	action->SetAttribute("operation", operation_to_svg(o).c_str());
	action->SetAttribute("in", size_to_string(insize).c_str());
	action->SetAttribute("out", size_to_string(outsize).c_str());
	Location::saveXml(action);
	parent->InsertEndChild(action);

	return action;

}

const Request* Action::get_serviced_request() const
{
	return nullptr;
}
