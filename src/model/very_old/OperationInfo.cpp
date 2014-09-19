/*
 * OperationInfo.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: thallock
 */

#include "model/OperationInfo.h"

#include <iomanip>

OperationInfo::OperationInfo() : OperationInfo{Store, none, none} {}
OperationInfo::OperationInfo(
		Operation o_,
		DumpsterSize in, DumpsterSize out) :
	o{o_},
	insize{in}, outsize{out} {}

#if 0
OperationInfo::OperationInfo(const OperationInfo& other) :
		o{other.o},
		insize{other.insize},
		outsize{other.outsize} {}
#endif

OperationInfo::~OperationInfo() {}

DumpsterSize OperationInfo::get_output_dumpster_size() const
{
	return outsize;
}

DumpsterSize OperationInfo::get_input_dumpster_size() const
{
	return insize;
}


Operation OperationInfo::get_operation() const
{
	return o;
}

std::string get_size_text(const OperationInfo& a)
{
	return get_size_text(a.get_input_dumpster_size()) + get_size_text(a.get_output_dumpster_size());
}

std::ostream& operator<<(std::ostream& os, const OperationInfo& a)
{
	return os << " a='" << std::left << std::setw(10) << operation_to_string(a.o) << "' " << get_size_text(a);
}

bool OperationInfo::operator ==(const OperationInfo& other)
{
	return other.o == o && other.insize == insize && other.outsize == outsize;
}
