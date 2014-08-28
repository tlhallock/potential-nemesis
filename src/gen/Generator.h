/*
 * Generator.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "Solution.h"
#include "model/Request.h"
#include "Parameters.h"

class Generator
{
public:
	Generator();
	virtual ~Generator();

	virtual Solution generate(const std::vector<Request>& requests, const Parameters &params) = 0;
};

#endif /* GENERATOR_H_ */
