/*
 * Operation.h
 *
 *  Created on: Aug 27, 2014
 *      Author: thallock
 */

#ifndef OPERATION_H_
#define OPERATION_H_

#include <string>

typedef enum
{
	smallest,
	small,
	big,
	biggest,
	none,
} DumpsterSize;

typedef enum
{
	PickUp,
	DropOff,
	Dump,
	Store,
	UnStore,
	Replace,
} Operation;

typedef enum
{
	lithe,
	normal,
	strong,
} TruckType;

std::string operation_to_string(Operation o);
std::string operation_to_svg(Operation o);

Operation char_to_operation(char c);

std::string size_to_string(DumpsterSize);
DumpsterSize string_to_size(const char *str);

std::string get_size_text(DumpsterSize size);

int get_points(Operation operation);

std::string truck_to_string(TruckType typ);
TruckType string_to_truck(const char * string);

#endif /* OPERATION_H_ */
