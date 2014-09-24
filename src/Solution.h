/*
 * Solution.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Route.h"

#include "XmlObject.h"

class City;

class Solution : public XmlRootObject
{
public:
	Solution(const City* city);
	Solution(const Solution &other);
	~Solution();

	bool service_next(int driver, const Action* action);

	sh_time_t get_time_taken() const;
	int get_num_requests_serviced() const;

	int get_num_drivers() const;
	const Route &get_route(int index) const;
	Route &get_route(int index);

	bool already_serviced(const Action* action) const;

	friend std::ostream& operator<<(std::ostream& os, const Solution& r);
	Solution& operator=(const Solution& other);

	void loadXml(const tinyxml2::XMLDocument* document);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLDocument* document) const;

	void validate();
private:
	const City* city;
	std::vector<Route> routes;

	bool *m_already_serviced;
};

#endif /* SOLUTION_H_ */
