/*
 * Route.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef ROUTE_H_
#define ROUTE_H_

#include "model/Action.h"
#include "model/City.h"

#include <vector>

class Solution;
class City;

class Route : public XmlObject
{
	friend class Solution;
public:
	Route(const City* city, int driver);
	Route(const Route &other);
	virtual ~Route();

	sh_time_t get_time_to_end() const;
	int get_num_requests_serviced() const;

	bool can_service_next(const Action* req) const;
	const Location &get_current_location() const;

	int get_num_actions() const;
	const Action* get_action(int index) const;
	const Action* get_last_action() const;

	const City* get_city() const;

	friend std::ostream& operator<<(std::ostream& os, const Route& r);
	virtual void loadXml(const tinyxml2::XMLElement* element);
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
private:
	void service_next(const Action* req);
	sh_time_t get_time_to(const int i) const;
	bool verify_indices() const;

	const City* city;
	int driver;
	std::vector<int> requests;
};

#endif /* ROUTE_H_ */
