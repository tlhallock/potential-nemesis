/*
 * Action.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Action.h"

#include <climits>
#include <iomanip>

Action::Action(const Location& l_, const Operation& o_, DumpsterSize in, DumpsterSize out) :
	Location(l_),
	o(o_),
	insize(in),
	outsize(out) {}

Action::~Action() {}

sh_time_t Action::get_time_taken(sh_time_t start_time, const Location& from) const
{
	return start_time + from.get_time_to(*this);
}

bool Action::follows_in_time(sh_time_t start_time, const Location& from) const
{
	sh_time_t time_taken = get_time_taken(start_time, from);
	return
#if CANT_HIT_TOO_EARLY
			time_taken > get_minimum_time() &&
#endif
			time_taken < get_maximum_time();
}

action_ptr get_start_action()
{
	return action_ptr {new Action{Location{0, 0}, Store, none, none}};
}

sh_time_t Action::get_minimum_time() const { return sh_time_min; }
sh_time_t Action::get_maximum_time() const { return sh_time_max; }

int Action::get_points() const { return 0; }

Operation Action::get_operation() const { return o; }

std::ostream& operator<<(std::ostream& os, const Action& a)
{
	return os << Location {a} << " a='" << std::left << std::setw(10) << operation_to_string(a.o) << "' " << get_size_text(a);
}

bool Action::satisfies(const action_ptr& r) const
{
	return false;
}

DumpsterSize Action::get_output_dumpster_size() const
{
	return outsize;
}

DumpsterSize Action::get_input_dumpster_size() const
{
	return insize;
}


namespace
{
inline std::string get_size_text(DumpsterSize size)
{
	switch(size)
	{
		case none:	       		return "0";
		case smallest:			return "1";
		case small:			return "2";
		case big:			return "3";
		case biggest:			return "4";
		default:			return "*";
	}
}
}
std::string get_size_text(const Action &a)
{
	return get_size_text(a.get_input_dumpster_size()) + get_size_text(a.get_output_dumpster_size());
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

void Action::loadXml(const tinyxml2::XMLElement* area)
{
	const char *op = area->Attribute("operation");
	if (op == nullptr)
	{
		std::cout << "No operation for action!!!!" << std::endl;
		exit(-1);
	}
	o = char_to_operation(*op);

	insize = string_to_size(area->Attribute("in"));
	outsize = string_to_size(area->Attribute("out"));
	Location::loadXml(area);
}

void Action::saveXml(std::ostream& out) const
{
	out << "\t\t<" << get_xml_name();
	out << " operation=\"" << operation_to_svg(o) << "\"";
	out << " in=\"" << size_to_string(insize) << "\"";
	out << " out=\"" << size_to_string(outsize) << "\">" << std::endl;
	Location::saveXml(out);
	// should have been better about this: this should save to an xml document too...
	child_save_xml(out);
	out << "\t\t</" << get_xml_name() << ">" << std::endl;
}

void Action::child_save_xml(std::ostream& out) const {}

std::string Action::get_xml_name() const
{
	return "action";
}
