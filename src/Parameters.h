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
};

#endif /* CONSTRAINTS_H_ */
