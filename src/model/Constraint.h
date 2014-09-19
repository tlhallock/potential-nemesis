/*
 * Constraint.h
 *
 *  Created on: Sep 19, 2014
 *      Author: thallock
 */

#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "model/Operation.h"
#include <set>

class LocationConstraint
{
	LocationConstraint(location l);
	~LocationConstraint();

	location get_location() const;
	void permit(TruckType type);
	bool permits(TruckType type) const;
private:
	location l;
	std::set<TruckType> types;
};

typedef std::map<const Operation, const location> operation_location_constraint;
bool satisfies_operation_constraint(const Action* action, const operation_location_constraint& constraint);

#endif /* CONSTRAINT_H_ */
