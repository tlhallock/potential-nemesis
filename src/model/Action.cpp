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

bool Action::follows(const Action& a) const
{
	return state_can_service(get_truck_state(), a.o);
}

TruckState Action::get_truck_state() const
{
	return operation_to_truck_state(o);
}

sh_time_t Action::get_time_taken(sh_time_t start_time, const Location& from) const
{
	return start_time + from.get_time_to(*this);
}

const Action& get_start_action()
{
	static Action *action;
	if (action == nullptr)
	{
		action = new Action{Location{0,0}, Dump};
	}
	return *action;
}

sh_time_t Action::get_minimum_time() const { return sh_time_min; }

sh_time_t Action::get_maximum_time() const { return sh_time_max; }

int Action::get_points() const { return 0; }

Operation Action::get_operation() const { return o; }

void Action::append_to(std::ostream& os) const
{
	os << " a=" << std::left << std::setw(10) << operation_to_string(o);
}
