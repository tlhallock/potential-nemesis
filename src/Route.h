/*
 * Route.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include "model/Action.h"

#include <vector>

class Optimizer;

class Route {
	friend class Optimizer;

public:
	Route();
	Route(const Route &other);
	virtual ~Route();

	sh_time_t get_time_taken() const;
	int get_num_requests_serviced() const;

	bool can_service_next(action_ptr req) const;
	void service_next(action_ptr req);
	const Location &get_current_location() const;

	int get_num_actions() const;
	const Action &get_action(int index) const;
	const action_ptr &get_last_action() const;

	bool already_serviced(const action_ptr &r) const;

	friend std::ostream& operator<<(std::ostream& os, const Route& r);
private:
	sh_time_t get_time_taken(const int i) const;

	std::vector<action_ptr> requests;
};

#endif /* ROUTE_H_ */
