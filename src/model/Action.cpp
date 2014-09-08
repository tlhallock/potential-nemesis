/*
 * Action.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Action.h"

#include <climits>
#include <iomanip>

Action::Action(const Location& l_, const Operation& o_) :
	Location(l_),
	o(o_) {}

Action::~Action() {}

sh_time_t Action::get_time_taken(sh_time_t start_time, const Location& from) const
{
	return start_time + from.get_time_to(*this);
}

bool Action::follows_in_time(sh_time_t start_time, const Location& from) const
{
	sh_time_t time_taken = get_time_taken(start_time, from);
	return time_taken > get_minimum_time() && time_taken < get_maximum_time();
}

action_ptr get_start_action()
{
	return action_ptr {new Action{Location{0, 0}, Dump}};
}

sh_time_t Action::get_minimum_time() const { return sh_time_min; }
sh_time_t Action::get_maximum_time() const { return sh_time_max; }

int Action::get_points() const { return 0; }

Operation Action::get_operation() const { return o; }

void Action::append_to(std::ostream& os) const
{
	os << " a=" << std::left << std::setw(10) << operation_to_string(o);
}

bool Action::satisfies(const action_ptr& r) const
{
	return false;
}
