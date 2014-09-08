/*
 * Constraints.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef CONSTRAINTS_H_
#define CONSTRAINTS_H_

class Parameters
{
public:
	Parameters();

	~Parameters();

	int get_num_drivers() const;
	int get_num_requests() const;

	int num_random_requests() const;
	int num_random_land_fills() const;
};

#endif /* CONSTRAINTS_H_ */
