/*
 * Route.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include "model/Request.h"
#include "model/Truck.h"

#include <vector>

class Optimizer;

class Route {
	friend class Optimizer;

public:
	Route();
	virtual ~Route();

	sh_time_t get_time_taken() const;
	TruckState get_truck_state() const;
	int get_num_requests_serviced() const;

	std::vector<Action> get_next_possibles() const;

	bool can_service_next(const Action &req) const;
	void service_next(const Action *req);

	friend std::ostream& operator<<(std::ostream& os, const Route& r);
private:
	sh_time_t get_time_taken(const int i) const;

	std::vector<const Action*> requests;
};

#endif /* ROUTE_H_ */
