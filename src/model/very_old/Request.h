/*
 * Request.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include "model/Location.h"
#include "model/OperationInfo.h"

#include "common.h"

#include <string>
#include <inttypes.h>
#include <iostream>
#include <set>

class Request : public Location, public OperationInfo
{
public:
	Request();
	Request(        const Location &&l,
			const OperationInfo &&info,
			sh_time_t start_time,
			sh_time_t stop_time);
	~Request();

	sh_time_t get_minimum_time() const;
	sh_time_t get_maximum_time() const;

	friend std::ostream& operator<<(std::ostream& os, const Request& a);
	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;

	void set_servicable_by(TruckType tt, bool value);
	void servicable_by_all();
private:
	sh_time_t start_time;
	sh_time_t stop_time;

	std::set<TruckType> truck_types;
};


#endif /* REQUEST_H_ */
