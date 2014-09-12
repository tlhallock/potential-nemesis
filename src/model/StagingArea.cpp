/*
 * StagingArea.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "model/StagingArea.h"

StagingArea::StagingArea() : Location {0,0}, wait_time{0}, max_containers{INT_MAX} {}

StagingArea::StagingArea(const Location &loc, sh_time_t wait_time_, int max_containers_) :
	Location{loc},
	wait_time (wait_time_),
	max_containers(max_containers_) {}

StagingArea::~StagingArea() {}

void StagingArea::loadXml(const tinyxml2::XMLElement* area)
{
	Location::loadXml(area);

	const tinyxml2::XMLElement* wait = area->FirstChildElement("wait");
	if (wait == nullptr)
	{
		std::cout << "While parsing landfill: no wait time." << std::endl;
	}
	else
	{
		wait->QueryUnsignedAttribute("time", &wait_time);
	}

	const tinyxml2::XMLElement* containers = area->FirstChildElement("containers");
	if (containers == nullptr)
	{
		std::cout << "While parsing landfill: no wait time." << std::endl;
	}
	else
	{
		containers->QueryUnsignedAttribute("max", &max_containers);
	}
}

void StagingArea::saveXml(std::ostream& out) const
{
	out << "\t\t<stagingarea>" << std::endl;
	Location::saveXml(out);
	out << "\t\t\t<wait time=\"" << wait_time << "\" />" << std::endl;
	out << "\t\t\t<containers max=\"" << max_containers << "\" />" << std::endl;
	out << "\t\t</stagingarea>" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const StagingArea& r)
{
	return os << Location {r} << " wait time = " << r.wait_time << ", max containers = " << r.max_containers;
}
