/*
 * City.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef CITY_H_
#define CITY_H_

#include "model/Action.h"
#include "model/StagingArea.h"

#include "XmlObject.h"


class City : public XmlRootObject
{
public:
	City();
	~City();

	// Creation
	void add_staging_area(Location l, int *inventories, int capacity);
	void add_land_fill(Location l);
	void add_request(Action *action);
	location add_location(const Location & l);

	// IO
	friend std::ostream& operator<<(std::ostream& os, const City& r);
	void loadXml(const tinyxml2::XMLDocument* document);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLDocument* document) const;
	std::ostream& save_to_matlab(std::ostream& out) const;

	// Stops
	int get_num_stops() const;
	const Action *get_stop(int index) const;
	const std::vector<const Action*> &get_all_stops() const;

	// Trucks
	int get_num_trucks() const;
	void add_truck(TruckType truck_type);
	location get_start_location(int driver) const;
	int get_start_action(int driver) const;

	// Location
	sh_time_t get_time_from(location i, location j) const;
	const Location& get_location(location l) const;

	// Staging areas
private:
	void refresh_distances();
	void add_stop(Action *action);

	std::vector<const Action *> all_actions;
	std::vector<Location> all_locations;
	std::vector<TruckType> truck_types;
	std::map<int, StagingArea> staging_areas;

	const Action* start_action;
	double *distances;
};

#endif /* CITY_H_ */
