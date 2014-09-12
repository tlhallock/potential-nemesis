/*
 * Landfills.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Landfills.h"

#include "generate.h"

#include "common.h"

Landfill::Landfill() : Location{0,0}, wait_time {0} {}
Landfill::Landfill(const Location &loc, sh_time_t wait_time_) :
	Location {loc},
	wait_time(wait_time_) {}

Landfill::~Landfill() {}

sh_time_t Landfill::get_wait_time() const
{
	return wait_time;
}

void Landfill::loadXml(const tinyxml2::XMLElement* landfill)
{
	Location::loadXml(landfill);

	const tinyxml2::XMLElement* wait = landfill->FirstChildElement("wait");
	if (wait == nullptr)
	{
		std::cout << "While parsing landfill: no wait time." << std::endl;
	}
	else
	{
		wait->QueryUnsignedAttribute("time", &wait_time);
	}
}

void Landfill::saveXml(std::ostream& out) const
{
	out << "\t\t<landfill>" << std::endl;
	Location::saveXml(out);
	out << "\t\t\t<wait time=\"" << wait_time << "\" />" << std::endl;
	out << "\t\t</landfill>" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Landfill& r)
{
	return os << Location {r} << " wait time = " << r.wait_time;
}
