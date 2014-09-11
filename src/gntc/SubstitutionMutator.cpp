/*
 * SubstitutionMutator.cpp
 *
 *  Created on: Sep 10, 2014
 *      Author: thallock
 */

#include "gntc/SubstitutionMutator.h"

SubstitutionMutator::SubstitutionMutator(Solver *slvr_) : Mutator{}, slvr {slvr_} {}
SubstitutionMutator::~SubstitutionMutator() {}

void SubstitutionMutator::mutate(const City& c, individual child)
{
}
