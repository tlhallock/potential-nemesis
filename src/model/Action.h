/*
 * Action.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "model/Operation.h"
#include "model/Location.h"

#include "common.h"

#include <iostream>
#include <memory>

class Request;

class Action : public Location
{
public:
	Action(const Location &l, const Operation &o, DumpsterSize in, DumpsterSize out);
	~Action();

	Operation get_operation() const;

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	bool follows_in_time(sh_time_t start_time, const Location &from) const;

	virtual sh_time_t get_minimum_time() const;
	virtual sh_time_t get_maximum_time() const;

	// rename this...
	virtual int get_points() const;
	virtual bool satisfies(const std::shared_ptr<const Action>  &r) const;

	virtual DumpsterSize get_output_dumpster_size() const;
	virtual DumpsterSize get_input_dumpster_size() const;

protected:
	virtual void append_to(std::ostream& os) const;

private:
	Operation o;

	DumpsterSize insize;
	DumpsterSize outsize;
};

typedef std::shared_ptr<const Action> action_ptr;

action_ptr get_start_action();

std::string get_size_text(const Action &a);

#endif /* ACTION_H_ */
