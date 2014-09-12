/*
 * Action.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef ACTION_H_
#define ACTION_H_

#define ACTION_NAME "action"
#define REQUEST_NAME "request"
#define FILL_LAND_NAME ("Fill land")

#include "model/Operation.h"
#include "model/Location.h"
#include "model/OperationInfo.h"

#include "common.h"

#include <iostream>
#include <memory>
#include <map>

#include "XmlObject.h"

class Request;

class Action : virtual public Location, public XmlObject, public OperationInfo
{
public:
	Action();
	Action(const Location &l, const Operation &o, DumpsterSize in, DumpsterSize out);
	~Action();

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	bool follows_in_time(sh_time_t start_time, const Location &from) const;

	// rename this...
	virtual int get_points() const;
	virtual bool satisfies(const Request *request) const;

	friend std::ostream& operator<<(std::ostream& os, const Action& a);

	virtual void loadXml(const tinyxml2::XMLElement* element);
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;

	virtual const Request *get_serviced_request() const;
};

typedef std::shared_ptr<const Action> action_ptr;

action_ptr get_start_action();

typedef std::map<const Operation, const Location> operation_location_constraint;
bool satisfies_operation_constraint(const action_ptr &action, const operation_location_constraint& constraint);

#endif /* ACTION_H_ */
