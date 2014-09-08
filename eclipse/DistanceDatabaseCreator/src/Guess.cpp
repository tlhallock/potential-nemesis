/*
 * Guess.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "Guess.h"

#include <float.h>

Guess::Guess() :
		cost(DBL_MAX), answer(-1) {}
Guess::Guess(double cost_, double answer_) :
		cost(cost_), answer(answer_) {}
Guess::~Guess() {}

bool Guess::is_better_than(const Guess &other) const
{
	return cost < other.cost;
}

double Guess::get_answer() const
{
	return answer;
}

double Guess::get_cost() const
{
	return cost;
}

std::ostream& operator<<(std::ostream& os, const Guess &g)
{
	os << "Cost: " << g.cost << " (" << g.cost * 25171.6 / 60 << " min) answer: " << g.answer << " ( " << g.answer / 60 << " min)" << std::endl;
	return os;
}
