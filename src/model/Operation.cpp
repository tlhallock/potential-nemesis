/*
 * Operation.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: thallock
 */

#include "model/Operation.h"

#include <iostream>

std::string operation_to_string(Operation a)
{
	switch (a)
	{
		case PickUp:
			return "Pick up full dumpster                ";
		case DropOff:
			return "Drop off empty dumpster              ";
		case Dump:
			return "Dump dumpster in landfill            ";
		case Store:
			return "Store empty dumpster                 ";
		case UnStore:
			return "Load empty dumpster from storage     ";
		case Replace:
			return "Replace full dumpster with empty one ";
		default:
			std::cout << "Uh Oh!!!! 45234523542435" << std::endl;
			return "Uknown";
	}
}

char operation_to_svg(Operation o)
{
	switch (o)
	{
		case PickUp:
			return 'P';
		case DropOff:
			return 'D';
		case Dump:
			return 'T';
		case Store:
			return 'S';
		case UnStore:
			return 'U';
		case Replace:
			return 'R';
		default:
			std::cout << "Uh Oh!!!! a62562362346fgagasdg" << std::endl;
			return '?';
	}
}
