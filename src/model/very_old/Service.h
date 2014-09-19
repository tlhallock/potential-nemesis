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
	Service();
	Service(const Request *req);
	~Service();

	virtual sh_time_t get_time_taken(sh_time_t start_time, const Location &from) const;
	bool follows_in_time(sh_time_t start_time, const Location &from) const;

	int get_points() const;
	bool satisfies(const Request *request) const;
	const Request *get_serviced_request() const;

	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
private:
	// TODO: Delete this pointer....
	const Request *req;
};

#endif /* SERVICE_H_ */
