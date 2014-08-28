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
	Stage,
	UnStage,
} Operation;

std::string action_to_string(Operation o);

#endif /* OPERATION_H_ */
