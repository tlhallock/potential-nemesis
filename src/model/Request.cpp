/*
 * Request.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Request.h"

#include <sstream>
#include <iomanip>

Request::Request() : Request{Location {0, 0}, Store, 0, sh_time_max, none, none} {}

Request::Request(Location l_,
		Operation a_,
		sh_time_t start_time_,
		sh_time_t stop_time_,
		DumpsterSize insize_,
		DumpsterSize outsize_) :
	Action{l_, a_, insize_, outsize_},
	o(a_),
	start_time(start_time_),
	stop_time(stop_time_) {}

Request::~Request() {}

sh_time_t Request::get_time_taken(sh_time_t start_time, const Location& from) const
{
	int64_t t1 = Action::get_time_taken(start_time, from);
	if (this->start_time > t1)
	{
		t1 = this->start_time;
	}
	return t1 + time_at_stop();
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

std::ostream& operator<<(std::ostream& os, const Request& a)
{
	return os << Action {a} << "\tat time [" << std::setw(5) << a.start_time << ":" << std::setw(5) << a.stop_time << "]";
}

bool Request::satisfies(const action_ptr &r) const
{
	return get_x() == r->get_x() && get_y() == r->get_y() && get_operation() == r->get_operation();
}

sh_time_t Request::time_at_stop() const
{
	return TIME_AT_HOUSE;
}

void Request::loadXml(const tinyxml2::XMLElement* landfill_list)
{
	Action::loadXml(landfill_list);
	const tinyxml2::XMLElement* window = landfill_list->FirstChildElement("window");
	window->QueryUnsignedAttribute("begin", &start_time);
	window->QueryUnsignedAttribute("end", &stop_time);
}
void Request::child_save_xml(std::ostream& out) const
{
	out << "\t\t\t<window begin=\"" << start_time << "\" end=\"" << stop_time << "\" />" << std::endl;
}
std::string Request::get_xml_name() const
{
	return "request";
}
