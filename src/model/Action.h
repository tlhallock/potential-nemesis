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
	Action(const Location &l, const Operation &o);
	~Action();

	Operation get_operation() const;

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	bool follows_in_time(sh_time_t start_time, const Location &from) const;

	virtual sh_time_t get_minimum_time() const;
	virtual sh_time_t get_maximum_time() const;

	// remame this...
	virtual int get_points() const;
	virtual bool satisfies(const std::shared_ptr<const Action>  &r) const;
protected:
	virtual void append_to(std::ostream& os) const;
private:
	Operation o;
};

typedef std::shared_ptr<const Action> action_ptr;

action_ptr get_start_action();


#endif /* ACTION_H_ */
