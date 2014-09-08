/*
 * Dump.cpp
 *
 *  Created on: Sep 8, 2014
 *      Author: thallock
 */

#include "model/FillLand.h"

FillLand::FillLand(const Landfill& l, DumpsterSize size_) :
	Action {l, Dump, size_, size_},
	landfill_cost(l.get_wait_time()),
	size(size_) {}

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
