/*
 * StagingArea.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: thallock
 */

#include "model/StagingArea.h"

#include "model/Action.h"

#include <iomanip>

namespace
{
	int default_inventories[4];
}

StagingArea::StagingArea() : StagingArea(0, 0, &default_inventories[0]) {}

StagingArea::StagingArea(location l, int32_t c, int32_t* ini) :
	loc{l},
	capacity{c}
{
	inventories.insert(std::pair<DumpsterSize, int32_t> {smallest, ini[0]});
	inventories.insert(std::pair<DumpsterSize, int32_t> {small   , ini[1]});
	inventories.insert(std::pair<DumpsterSize, int32_t> {big     , ini[2]});
	inventories.insert(std::pair<DumpsterSize, int32_t> {biggest , ini[3]});
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

void StagingArea::loadXml(const tinyxml2::XMLElement* element)
{
	capacity = INT_MAX;
	element->QueryIntAttribute("max", &capacity);
	loc = 0;
	element->QueryIntAttribute("loc", &loc);

	const tinyxml2::XMLElement* inv = element->FirstChildElement("inv");
	while (inv != nullptr)
	{
		const char *dumpster_string = inv->Attribute("type");
		if (dumpster_string == nullptr)
		{
			continue;
		}
		DumpsterSize size = string_to_size(dumpster_string);
		int num = 0;
		inv->QueryIntAttribute("val", &num);

		inventories.insert(std::pair<DumpsterSize, int32_t> {size, num});

		inv = inv->NextSiblingElement("inv");
	}
}

tinyxml2::XMLElement* StagingArea::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* containers = parent->GetDocument()->NewElement("yard");

	containers->SetAttribute("max", capacity);
	containers->SetAttribute("loc", loc);

	auto end = inventories.end();
	for (auto it = inventories.begin(); it != end; ++it)
	{
		tinyxml2::XMLElement* inv = parent->GetDocument()->NewElement("inv");
		inv->SetAttribute("type", size_to_string(it->first).c_str());
		inv->SetAttribute("val", it->second);
		containers->InsertEndChild(inv);
	}

	parent->InsertEndChild(containers);

	return containers;
}

std::ostream& StagingArea::save_to_matlab(std::ostream& out) const
{
	out << "struct(";
	out << "location\", " << loc << ", ";
	out << "\"capacity\", " << capacity << ", ";

	auto end = inventories.end();
	for (auto it = inventories.begin(); it != end; ++it)
	{
		out << "\"initial_" << size_to_string(it->first) << "\", " << it->second << ", ";
	}

	return out << ");" << std::endl;
}

void StagingArea::set_num_of_size(DumpsterSize size, int32_t number)
{
	inventories.insert(std::pair<DumpsterSize, int32_t> {size, number});
}

int StagingArea::get_num_of_size(DumpsterSize size) const
{
	auto it = inventories.find(size);
	if (it == inventories.end())
	{
		return 0;
	}
	return it->second;
}

int StagingArea::get_num_dumpsters() const
{
	int sum = 0;
	auto end = inventories.end();
	for (auto it = inventories.begin(); it != end; ++it)
	{
		sum += it->second;
	}
	return sum;
}

bool StagingArea::can_apply(const Action* action) const
{
	if (action->get_location() != loc)
	{
		return true;
	}

	if (action->get_operation() == Store)
	{
		return get_num_dumpsters() + 1 <= capacity;
	}
	if (action->get_operation() != UnStore)
	{
		return true;
	}

	DumpsterSize size = action->get_output_dumpster_size();
	auto it = inventories.find(size);
	if (it == inventories.end())
	{
		std::cout << "No inventory set for size " << size_to_string(size) << std::endl;
		die();
	}
	if (it->second <= 0)
	{
		return false;
	}

	return true;
}

void StagingArea::applied(const Action* action)
{
	if (action->get_location() != loc)
	{
		return;
	}

	if (!can_apply(action))
	{
		std::cout << "Impossible inventory!" << std::endl;
		die();
	}

	int increment = 0;
	DumpsterSize size;
	Operation o = action->get_operation();
	if (o == Store)
	{
		increment = 1;
		size = action->get_input_dumpster_size();
	}
	else if (o == UnStore)
	{
		increment = -1;
		size = action->get_output_dumpster_size();
	}
	else
	{
		return;
	}

	auto it = inventories.find(size);
	if (it == inventories.end())
	{
		std::cout << "No inventory set for size " << size_to_string(size) << std::endl;
		die();
	}

	it->second += increment;
}


std::ostream& operator<<(std::ostream &os, const StagingArea& area)
{
	os << "[cap:" << std::setw(10) << area.capacity << "]";
	os << "[loc:" << std::setw(5) << area.loc << "]";
	auto end = area.inventories.end();
	for (auto it = area.inventories.begin(); it != end; ++it)
	{
		os << "[inv:t=" << size_to_string(it->first) << ",n=" << it->second << "]";
	}
	return os;
}
