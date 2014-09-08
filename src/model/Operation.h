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
	PickUp,
	DropOff,
	Dump,
	Store,
	UnStore,
	Replace,
} Operation;

std::string operation_to_string(Operation o);
char operation_to_svg(Operation o);

#endif /* OPERATION_H_ */
