/*
 * Service.h
 *
 *  Created on: Sep 12, 2014
 *      Author: thallock
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include "model/Action.h"
#include "model/Request.h"

class Service : public Action
{
public:
	~Service();
	Service(const Request *req);

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	int get_points() const;

	bool satisfies(const Request *request) const;

	const Request *get_serviced_request() const;

private:
	// TODO: Delete this pointer....
	const Request *req;
};

#endif /* SERVICE_H_ */
