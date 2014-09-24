/*
 * StagingArea.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: thallock
 */

#include "model/StagingArea.h"

namespace
{
	int default_inventories[4];
}

StagingArea::StagingArea() : StagingArea(0, 0, &default_inventories[0]) {}

StagingArea::StagingArea(location l, int32_t c, int32_t* ini) :
	loc{l},
	capacity{c}
{
	for (int i = 0; i < 4; i++)
	{
		initial_capacities[i] = ini[i];
	}
}

StagingArea::~StagingArea() {}

int StagingArea::get_location() const
{
	return loc;
}

int StagingArea::get_capacity() const
{
	return capacity;
}


int StagingArea::get_capacity(int ndx) const
{
	return initial_capacities[ndx];
}

void StagingArea::loadXml(const tinyxml2::XMLElement* element)
{
	capacity = INT_MAX;
	element->QueryIntAttribute("max", &capacity);
	loc = 0;
	element->QueryIntAttribute("loc", &loc);
}

tinyxml2::XMLElement* StagingArea::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* containers = parent->GetDocument()->NewElement("yard");

	containers->SetAttribute("max", capacity);
	containers->SetAttribute("loc", loc);
	parent->InsertEndChild(containers);

	return containers;
}

std::ostream& StagingArea::save_to_matlab(std::ostream& out) const
{
	out << "struct(";
	out << "location\", " << loc << ", ";
	out << "\"capacity\", " << capacity << ", ";

	for (int i = 0; i < 4; i++)
	{
		out << "\"initial" << i << "\", " << initial_capacities[i] << ", ";
	}


	return out << ");" << std::endl;
}
