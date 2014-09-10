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
	int num_random_requests() const;
	int num_random_land_fills() const;
	int num_random_staging_areas() const;
	double get_scale() const;
};

#endif /* CONSTRAINTS_H_ */
