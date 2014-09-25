/*
 * Operation.cpp
 *
 *  Created on: Aug 27, 2014
 *      Author: thallock
 */

#include "model/Operation.h"

#include "common.h"

#include <iostream>

#include <string.h>

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
			die();
			return "Uknown";
	}
}

std::string operation_to_svg(Operation o)
{
	switch (o)
	{
		case PickUp:
			return "P";
		case DropOff:
			return "D";
		case Dump:
			return "T";
		case Store:
			return "S";
		case UnStore:
			return "U";
		case Replace:
			return "R";
		default:
			std::cout << "Uh Oh!!!! a62562362346fgagasdg" << std::endl;
			die();
			return "?";
	}
}

Operation char_to_operation(char c)
{
	switch (c)
	{
		case 'P':
			return PickUp;
		case 'D':
			return DropOff;
		case 'T':
			return Dump;
		case 'S':
			return Store;
		case 'U':
			return UnStore;
		case 'R':
			return Replace;
		default:
			std::cout << "Uh Oh!!!! agdasdgadsg" << std::endl;
			die();
			return Store;
	}
}

std::string size_to_string(DumpsterSize size)
{
	switch(size)
	{
		case smallest:
			return "smallest";
		case small:
			return "small";
		case big:
			return "big";
		case biggest:
			return "biggest";
		case none:
			return "none";
		default:
			std::cout << "Unknown dumpster size!" << std::cout;
			die();
	}
	return "unknown";
}

DumpsterSize string_to_size(const char* str)
{
	if (str == nullptr)
	{
		std::cout << "Null in dumpster size!!!!" << std::endl;
		die();
	}
	else if (strcmp(str, "smallest") == 0)
	{
		return smallest;
	}
	else if (strcmp(str, "small") == 0)
	{
		return small;
	}
	else if (strcmp(str, "big") == 0)
	{
		return big;
	}
	else if (strcmp(str, "biggest") == 0)
	{
		return biggest;
	}
	else if (strcmp(str, "none") == 0)
	{
		return none;
	}
	else
	{
		std::cout << "Unknown dumpster size string: " << str << std::endl;
		die();
		return smallest;
	}
}


std::string get_size_text(DumpsterSize size)
{
	switch(size)
	{
		case none:	       		return "0";
		case smallest:			return "1";
		case small:			return "2";
		case big:			return "3";
		case biggest:			return "4";
		default:			return "*";
	}
}

int get_points(Operation operation)
{
	switch (operation)
	{
		case PickUp:
			return 1;
		case DropOff:
			return 1;
		case Dump:
			return 0;
		case Store:
			return 0;
		case UnStore:
			return 0;
		case Replace:
			return 2;
		default:
			std::cout << "Uh Oh!!!! fdsfdlkjafd" << std::endl;
			die();
			return -1;
	}
}

std::string truck_to_string(TruckType typ)
{
	switch (typ)
	{
		case lithe:
			return "1";
		case normal:
			return "2";
		case strong:
			return "3";
	}
	return "2";
}

TruckType string_to_truck(const char *string)
{
	if (strcmp(string, "1") == 0)
	{
		return lithe;
	}
	else if (strcmp(string, "2") == 0)
	{
		return normal;

	}
	else if (strcmp(string, "3") == 0)
	{
		return strong;
	}
	return normal;
}
