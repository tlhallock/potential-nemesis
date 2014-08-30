/*
 * Solver.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: rever
 */

#include "opt/Solver.h"

Solver::Solver(const Parameters &p_) : p(p_) {}
Solver::~Solver() {}

const Parameters Solver::get_params() const
{
	return p;
}
