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

std::string operation_to_string(Operation o);
std::string operation_to_svg(Operation o);

Operation char_to_operation(char c);

std::string size_to_string(DumpsterSize);
DumpsterSize string_to_size(const char *str);

std::string get_size_text(DumpsterSize size);

#endif /* OPERATION_H_ */
