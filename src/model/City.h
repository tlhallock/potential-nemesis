/*
 * City.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef CITY_H_
#define CITY_H_

#include "model/Action.h"

#include "XmlObject.h"


class City : public XmlRootObject
{
public:
	City();
	~City();

	int get_start_location(int driver) const;
	int get_start_action(int driver) const;

	int get_num_stops() const;
	const Action *get_stop(int index) const;
	const std::vector<const Action*> &get_all_stops() const;

	sh_time_t get_time_from(location i, location j) const;

	void add_stop(Action *action);

	friend std::ostream& operator<<(std::ostream& os, const City& r);

	void loadXml(const tinyxml2::XMLDocument* document);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLDocument* document) const;

	location add_location(const Location & l);

	int get_num_trucks() const;
	void add_truck(TruckType truck_type);

	const Location& get_location(location l) const;
private:
	std::vector<const Action *> all_actions;
	std::vector<Location> all_locations;
	std::vector<TruckType> truck_types;
	const Action* start_action;
};

#endif /* CITY_H_ */
