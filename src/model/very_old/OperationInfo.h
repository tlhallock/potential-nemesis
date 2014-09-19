/*
 * OperationInfo.h
 *
 *  Created on: Sep 12, 2014
 *      Author: thallock
 */

#ifndef OPERATIONINFO_H_
#define OPERATIONINFO_H_

#include "XmlObject.h"

#include "model/Operation.h"
#include <iostream>

class OperationInfo
{
public:
	OperationInfo();
	OperationInfo(Operation o, DumpsterSize in, DumpsterSize ou);
	virtual ~OperationInfo();


	friend std::ostream& operator<<(std::ostream& os, const OperationInfo& a);
	bool operator==(const OperationInfo& other);

	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
protected:
};

std::string get_size_text(const OperationInfo &r);

#endif /* OPERATIONINFO_H_ */
