/*
 * Guess.h
 *
 *  Created on: Sep 7, 2014
 *      Author: thallock
 */

#ifndef GUESS_H_
#define GUESS_H_

#include <iostream>

class Guess
{
public:
	Guess();
	Guess(double cost, double answer);
	~Guess();

	bool is_better_than(const Guess &other) const;

	double get_answer() const;
	double get_cost() const;

	friend std::ostream& operator<<(std::ostream& os, const Guess &g);
private:
	double cost;
	double answer;
};

#endif /* GUESS_H_ */
