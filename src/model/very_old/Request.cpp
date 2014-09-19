/*
 * Request.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Request.h"

#include <sstream>
#include <iomanip>

Request::Request() :
	Location{},
	OperationInfo{},
	start_time {0},
	stop_time{sh_time_max}
{
	servicable_by_all();
}

Request::Request(const Location &&l_,
		const OperationInfo &&info,
		sh_time_t start_time_,
		sh_time_t stop_time_) :
	Location{l_},
	OperationInfo{info},
	start_time(start_time_),
	stop_time(stop_time_)
{
	servicable_by_all();
}

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


std::string get_size_text(const Request &r)
{
	return get_size_text(r.get_input_dumpster_size()) + get_size_text(r.get_output_dumpster_size());
}

void Request::set_servicable_by(TruckType tt, bool value)
{
	auto it = truck_types.find(tt);
	if (it == truck_types.end())
	{
		if (value)
		{
			truck_types.insert(tt);
		}
	}
	else
	{
		if (!value)
		{
			truck_types.erase(tt);
		}
	}
}

void Request::servicable_by_all()
{
	set_servicable_by(lithe, true);
	set_servicable_by(strong, true);
	set_servicable_by(normal, true);
}
