/*
 * Optimizer.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef OPTIMIZER_H_
#define OPTIMIZER_H_

#include "model/Action.h"
#include <vector>

int random_decreasing_probability(int max, double rate = .9);
action_ptr get_close(const Location &current_location, std::vector<action_ptr> *possibles);

#endif /* OPTIMIZER_H_ */
