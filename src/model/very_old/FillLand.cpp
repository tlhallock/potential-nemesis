/*
 * Dump.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: thallock
 */

#include "model/FillLand.h"


FillLand::FillLand(const Landfill& l, DumpsterSize size_) :
	Action {l, OperationInfo {Dump, size_, size_}},
	landfill_cost(l.get_wait_time()),
	size(size_) {}

FillLand::FillLand() : FillLand {Landfill{}, none} {}

FillLand::~FillLand() {}

sh_time_t FillLand::get_time_taken(sh_time_t start_time, const Location& from) const
{
	return Action::get_time_taken(start_time, from) + landfill_cost;
}

DumpsterSize FillLand::get_output_dumpster_size() const
{
	return size;
}

DumpsterSize FillLand::get_input_dumpster_size() const
{
	return size;
}

void FillLand::loadXml(const tinyxml2::XMLElement* landfill_list)
{
	Action::loadXml(landfill_list);
}

void FillLand::child_save_xml(std::ostream& out) const
{
}


std::string FillLand::get_xml_name() const
{
	return FILL_LAND_NAME ;
}
