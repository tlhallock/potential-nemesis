/*
 * Metric.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef METRIC_H_
#define METRIC_H_

#include "opt/Cost.h"
#include "Solution.h"

class Metric
{
public:
	Metric();
	virtual ~Metric();

	virtual double get_cost(const Cost &c) = 0;
};

#endif /* METRIC_H_ */
