/*
 * SpokeGenerator.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef SPOKEGENERATOR_H_
#define SPOKEGENERATOR_H_

#include "gen/Generator.h"

class SpokeGenerator : public Generator
{
public:
	SpokeGenerator();
	virtual ~SpokeGenerator();

	Solution *generate(const std::vector<Request>& original_requests, const Parameters &params);
};

#endif /* SPOKEGENERATOR_H_ */
