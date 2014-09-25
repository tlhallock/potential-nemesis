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

#define START_INDEX (-1)



class IntermediateAction
{
public:
	IntermediateAction(int dest);
	~IntermediateAction();

	void add_alternative(const std::vector<int>& path);
	int get_num_paths() const;

	const std::vector<std::vector<int>>& get_alternatives() const;

	friend std::ostream& operator<<(std::ostream& os, const IntermediateAction& action);
private:
	int dest;
	std::vector<std::vector<int>> alternatives;
};
IntermediateAction *create_intermediate_action(const std::vector<const Action*>& all, int from, int to);


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
	const Action* get_start_action(int driver) const;

	// Location
	sh_time_t get_time_from(location i, location j) const;
	const Location& get_location(location l) const;

	// Staging areas
	const std::map<const int, const StagingArea>& get_staging_areas() const;

	// Reduced
	const std::vector<int>& get_requests() const;
	const IntermediateAction* get_intermediates(int i, int j) const;
private:
	void refresh_distances();
	void clear_intermediates() const;
	void refresh_intermediates() const;
	void add_stop(Action *action);

	std::vector<const Action *> all_actions;
	std::vector<Location> all_locations;
	std::vector<TruckType> truck_types;
	std::map<const int, const StagingArea> staging_areas;

	Action* start_action;

	// cached entries
	double *distances;
	mutable std::vector<int> request_indices;
	mutable IntermediateAction **intermediate_actions;
	// not used yet...
	mutable sh_time_t *minimum_times;
};

#endif /* CITY_H_ */
