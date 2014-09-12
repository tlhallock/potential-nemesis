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

std::ostream& operator<<(std::ostream& os, const StagingArea& r)
{
	return os << Location {r} << " wait time = " << r.wait_time << ", max containers = " << r.max_containers;
}

void StagingArea::loadXml(const tinyxml2::XMLElement* area)
{
	Location::loadXml(area);

	const tinyxml2::XMLElement* wait = area->FirstChildElement("wait");
	if (wait == nullptr)
	{
		std::cout << "While parsing staging area: no wait time." << std::endl;
	}
	else
	{
		wait->QueryUnsignedAttribute("time", &wait_time);
	}

	const tinyxml2::XMLElement* containers = area->FirstChildElement("containers");
	if (containers == nullptr)
	{
		std::cout << "While parsing staging area: no wait time." << std::endl;
	}
	else
	{
		containers->QueryUnsignedAttribute("max", &max_containers);
	}
}

tinyxml2::XMLElement* StagingArea::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* area = parent->GetDocument()->NewElement("stagingarea");

	Location::saveXml(area);
	tinyxml2::XMLElement* wait = parent->GetDocument()->NewElement("wait");
	wait->SetAttribute("time", wait_time);
	area->InsertEndChild(wait);
	tinyxml2::XMLElement* containers = parent->GetDocument()->NewElement("containers");
	containers->SetAttribute("max", max_containers);
	area->InsertEndChild(containers);

	parent->InsertEndChild(area);
	return area;
}
