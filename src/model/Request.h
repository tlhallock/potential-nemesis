/*
 * Request.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "model/Action.h"
#include "model/Location.h"
#include "model/OperationInfo.h"

#include "common.h"

#include <string>
#include <inttypes.h>
#include <iostream>

class Request : virtual public Location, public XmlObject, public OperationInfo
{
public:
	Request();
	Request(        Location l,
			Operation a,
			sh_time_t start_time,
			sh_time_t stop_time,
			DumpsterSize in,
			DumpsterSize out);
	~Request();

	sh_time_t get_minimum_time() const;
	sh_time_t get_maximum_time() const;

	friend std::ostream& operator<<(std::ostream& os, const Request& a);
	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
private:
	sh_time_t start_time;
	sh_time_t stop_time;
};


#endif /* REQUEST_H_ */
