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

#include "common.h"

#include <iostream>
#include <memory>
#include <map>

#include "XmlObject.h"

class Action
{
public:
	Action();
	Action(
			Operation o_,
			DumpsterSize insize_,
			DumpsterSize outsize_,
			sh_time_t min,
			sh_time_t max,
			sh_time_t time,
			location location_);
	~Action();

	DumpsterSize get_output_dumpster_size() const;
	DumpsterSize get_input_dumpster_size() const;

	sh_time_t get_minimum_time() const;
	sh_time_t get_maximum_time() const;
	sh_time_t get_wait_time() const;

	Operation get_operation() const;

	// rename this...
	int get_points() const;

	int get_index() const;
	void set_index(int ndx);

	location get_location() const;

	friend std::ostream& operator<<(std::ostream& os, const Action& a);

	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;

	std::ostream &save_to_matlab(std::ostream &out) const;
private:
	Operation o;

	DumpsterSize insize;
	DumpsterSize outsize;

	sh_time_t min_time;
	sh_time_t max_time;

	sh_time_t time_required;

	location loc;

	int index;
};

#endif /* ACTION_H_ */
