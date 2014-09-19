/*
 * Service.cpp
 *
 *  Created on: Sep 12, 2014
 *      Author: thallock
 */

#include "model/Service.h"

Service::Service(const Request *req_) : Action {*req_, *req_}, req{req_} {}
Service::Service() : Action {}, req {nullptr} {}
Service::~Service() {}

sh_time_t Service::get_time_taken(sh_time_t start_time, const Location& from) const
{
	int64_t t1 = Action::get_time_taken(start_time, from);
	if (req->get_minimum_time() > t1)
	{
		t1 = req->get_minimum_time();
	}
	return t1 + TIME_AT_HOUSE;
}

int Service::get_points() const
{
	return 1;
}

bool Service::satisfies(const Request *r) const
{
	return get_x() == r->get_x()
		&& get_y() == r->get_y()
		&& get_operation() == r->get_operation();
}


const Request* Service::get_serviced_request() const
{
	return req;
}

void Service::loadXml(const tinyxml2::XMLElement* element)
{
	OperationInfo::loadXml(element);
	Location::loadXml(element);
}

tinyxml2::XMLElement* Service::saveXml(tinyxml2::XMLElement* parent) const
{
	tinyxml2::XMLElement* service = parent->GetDocument()->NewElement("service");
	OperationInfo::saveXml(service);
	Location::saveXml(service);
	parent->InsertEndChild(service);
	return service;
}
