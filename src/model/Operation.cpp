/*
 * Operation.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: thallock
 */

#include "model/Operation.h"

#include <iostream>

std::string action_to_string(Operation a)
{
	switch(a)
	{
	case PickUp:
		return "PickUp";
	case DropOff:
		return "DropOff";
	case Dump:
		return "Dump";
	case Stage:
		return "Stage";
	case UnStage:
		return "UnStage";
	default:
		std::cout << "Uh Oh!!!! 45234523542435" << std::endl;
		return "Uknown";
	}
}
