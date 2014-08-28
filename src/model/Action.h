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
#include "model/Truck.h"

#include "common.h"

#include <iostream>

class Action : public Location
{
public:
	Action(const Location &l, const Operation &o);
	~Action();

	bool follows(const Action &a) const;
	TruckState get_truck_state() const;
	Operation get_operation() const;

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;

	virtual sh_time_t get_minimum_time() const;
	virtual sh_time_t get_maximum_time() const;

	virtual int get_points() const;
protected:
	virtual void append_to(std::ostream& os) const;
private:
	Operation o;
};

const Action &get_start_action();

#endif /* ACTION_H_ */
