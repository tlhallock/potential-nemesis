/*
 * Guess.cpp
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#include "Guess.h"

#include "config.h"

#include <float.h>

Guess::Guess() :
		cost(DBL_MAX), answer(-1) {}
Guess::Guess(double cost_, double answer_) :
		cost(cost_), answer(answer_) {}
Guess::~Guess() {}

bool Guess::is_better_than(const Guess &other) const
{
#if DONT_INCLUDE_ZERO_ANSWERS
	if (other.get_answer() == 0)
	{
		return true;
	}
	else if (get_answer() == 0)
	{
		return false;
	}
#endif
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
	os << "Cost: " << g.cost << " (" << g.cost * 7128.76 / 60 << " min) answer: " << g.answer << " ( " << g.answer / 60 << " min)" << std::endl;
	return os;
}
