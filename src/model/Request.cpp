/*
 * Request.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Request.h"

#include <sstream>
#include <iomanip>

Request::Request(Location l_, Operation a_, sh_time_t start_time_, sh_time_t stop_time_) :
	Action{l_, a_},
	o(a_),
	start_time(start_time_),
	stop_time(stop_time_){}

Request::~Request() {}

sh_time_t Request::get_time_taken(sh_time_t start_time, const Location& from) const
{
	int64_t t1 = Action::get_time_taken(start_time, from);
	if (t1 > this->start_time)
	{
		return t1;
	}

	return this->start_time;
}

sh_time_t Request::get_minimum_time() const
{
	return start_time;
}

sh_time_t Request::get_maximum_time() const
{
	return stop_time;
}

int Request::get_points() const
{
	return 1;
}

void Request::append_to(std::ostream& os) const
{
	Action::append_to(os);
	os << "\tat time [" << std::setw(5) << start_time << ":" << std::setw(5) << stop_time << "]";
}

bool Request::satisfies(const action_ptr &r) const
{
	return get_x() == r->get_x() && get_y() == r->get_y() && get_operation() == r->get_operation();
}
