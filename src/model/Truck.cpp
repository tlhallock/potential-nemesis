/*
 * Truck.cpp
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#include "model/Truck.h"

#include <iostream>

bool state_can_service(TruckState s, Operation a)
{
	switch(s)
	{
	case NoDumpster:
		return a == PickUp || a == UnStage;
	case EmptyDumpster:
		return a == DropOff || a == Stage;
	case FullDumpster:
		return a == Dump;
	default:
		std::cout << "Should never reach this code." << std::endl;
	}
	return false;
}

TruckState operation_to_truck_state(Operation o)
{
	switch (o)
	{
	case PickUp:
		return FullDumpster;
	case DropOff:
		return NoDumpster;
	case Dump:
		return EmptyDumpster;
	case Stage:
		return NoDumpster;
	case UnStage:
		return EmptyDumpster;
	default:
		std::cout << "Never reach here." << std::endl;
		return EmptyDumpster;
	}
}
