/*
 * Location.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Location.h"

#include <cmath>
#include <iomanip>
#include <sstream>

Location::Location() : Location{0, 0} {};
Location::Location(double x_, double y_) : x{x_}, y{y_} {}
Location::Location(const Location& loc) :
		Location{loc.get_x(), loc.get_y()} {}
Location::~Location() {}

std::ostream& operator<<(std::ostream& os, const Location& r)
{
	return os << "{" << std::setw(10) << r.x << " , " << std::setw(10) << r.y << " }";
}

sh_time_t Location::get_time_to(const Location& l) const
{
	double xd = l.x - x;
	double yd = l.y - y;

	return (int64_t) sqrt(xd * xd + yd * yd);
}

bool Location::is_same_location(const Location& other) const
{
	return x == other.x && y == other.y;
}

double Location::get_x() const
{
	return x;
}

double Location::get_y() const
{
	return y;
}

bool Location::operator <(const Location& other) const
{
	if (x == other.x)
	{
		return y < other.y;
	}
	else
	{
		return x < other.x;
	}
}

bool Location::operator ==(const Location& other) const
{
	return x == other.x && y == other.y;
}

#if 0
std::string Location::serialize() const
{
	std::stringstream ss;
	ss << "[" << x << "," << y << "]";
	return ss.str();
}
#endif

void Location::loadXml(const tinyxml2::XMLElement* element)
{
	const tinyxml2::XMLElement* loc = element; // element->FirstChildElement("location");
	if (loc == nullptr)
	{
		std::cout << "Error parsing location: no location!" << std::endl;
	}
	else
	{
		loc->QueryDoubleAttribute("x", &x);
		loc->QueryDoubleAttribute("y", &y);
	}
}
tinyxml2::XMLElement* Location::saveXml(tinyxml2::XMLElement* element) const
{
	tinyxml2::XMLElement* location = element->GetDocument()->NewElement("location");
	location->SetAttribute("x", x);
	location->SetAttribute("y", y);
	element->InsertEndChild(location);
	return location;
}
