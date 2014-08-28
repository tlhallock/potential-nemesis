/*
 * RandomNextGenerator.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef RANDOMNEXTGENERATOR_H_
#define RANDOMNEXTGENERATOR_H_

#include "gen/Generator.h"

class RandomNextGenerator : public Generator
{
public:
	RandomNextGenerator();
	virtual ~RandomNextGenerator();

	Solution *generate(const std::vector<Request>& original_requests, const Parameters &params);

private:
	void generate(const std::vector<Request>& original_requests, Route &output, bool *serviced);
};

#endif /* RANDOMNEXTGENERATOR_H_ */
