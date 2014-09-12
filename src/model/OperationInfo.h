/*
 * OperationInfo.h
 *
 *  Created on: Sep 12, 2014
 *      Author: thallock
 */

#ifndef OPERATIONINFO_H_
#define OPERATIONINFO_H_

#include "model/Operation.h"
#include <iostream>

class OperationInfo
{
public:
	OperationInfo();
	OperationInfo(Operation o, DumpsterSize in, DumpsterSize ou);
	virtual ~OperationInfo();

	DumpsterSize get_output_dumpster_size() const;
	DumpsterSize get_input_dumpster_size() const;

	Operation get_operation() const;

	friend std::ostream& operator<<(std::ostream& os, const OperationInfo& a);
protected:
	Operation o;

	DumpsterSize insize;
	DumpsterSize outsize;
};

std::string get_size_text(const OperationInfo &r);

#endif /* OPERATIONINFO_H_ */
