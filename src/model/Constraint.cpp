/*
 * Constraint.cpp
 *
 *  Created on: Sep 19, 2014
 *      Author: thallock
 */

#include <model/Constraint.h>

LocationConstraint::LocationConstraint(location l_) : l(l_) {}
LocationConstraint::~LocationConstraint() {}

bool satisfies_operation_constraint(const Action* action, const operation_location_constraint& constraint)
{
	auto it = constraint.find(action->get_operation());
	if (it == constraint.end())
	{
		return true;
	}

	return action->get_location() == it->second;
}

location LocationConstraint::get_location() const
{
	return l;
}

void LocationConstraint::permit(TruckType type)
{
	types.insert(type);
}

bool LocationConstraint::permits(TruckType type) const
{
	return types.find(type) != types.end();
}
