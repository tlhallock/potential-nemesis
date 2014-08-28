/*
 * Truck.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef TRUCK_H_
#define TRUCK_H_

#include "model/Operation.h"

typedef enum
{
	NoDumpster,
	EmptyDumpster,
	FullDumpster,
} TruckState;

bool state_can_service(TruckState, Operation);

TruckState operation_to_truck_state(Operation o);

#endif /* TRUCK_H_ */
