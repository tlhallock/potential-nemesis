/*
 * Request.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Request.h"

#include <sstream>
#include <iomanip>

Request::Request() : Request{Location{}, Store, 0, sh_time_max, none, none} {}

Request::Request(Location l_,
		Operation a_,
		sh_time_t start_time_,
		sh_time_t stop_time_,
		DumpsterSize insize_,
		DumpsterSize outsize_) :
	Location{l_},
	OperationInfo{a_, insize_, outsize_},
	start_time(start_time_),
	stop_time(stop_time_) {}

Request::~Request() {}

sh_time_t Request::get_minimum_time() const
{
	return start_time;
}

sh_time_t Request::get_maximum_time() const
{
	return stop_time;
}

std::ostream& operator<<(std::ostream& os, const Request& a)
{
	return os << OperationInfo {a} << "\tat time [" << std::setw(5) << a.start_time << ":" << std::setw(5) << a.stop_time << "]";
}

void Request::loadXml(const tinyxml2::XMLElement* element)
{
	Location::loadXml(element);
	const tinyxml2::XMLElement* window = element->FirstChildElement("window");
	window->QueryUnsignedAttribute("begin", &start_time);
	window->QueryUnsignedAttribute("end", &stop_time);
}

tinyxml2::XMLElement* Request::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* action = Location::saveXml(parent);
	tinyxml2::XMLElement* window = parent->GetDocument()->NewElement("window");
	window->SetAttribute("begin", start_time);
	window->SetAttribute("end", stop_time);
	action->InsertEndChild(window);
	return action;
}

std::string get_size_text(const Request &r)
{
	return get_size_text(r.get_input_dumpster_size()) + get_size_text(r.get_output_dumpster_size());
}
