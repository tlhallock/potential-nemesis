/*
 * City.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef CITY_H_
#define CITY_H_

#include "model/StagingArea.h"
#include "model/Landfills.h"
#include "model/Request.h"

class Solution;

class City
{
public:
	City();
	~City();

	int get_num_requests() const;
	const Request &get_request(int i) const;

	int get_num_land_fills() const;
	const Landfill& get_land_fill(int index) const;
	const Landfill &get_closest_landfill(const Location &l) const;

	int get_num_staging_areas() const;
	const StagingArea &get_staging_area(int idx) const;

	void set_requests(std::vector<Request> requests);
	void set_land_fills(std::vector<Landfill> land_fills);
	void set_staging_areas(std::vector<StagingArea> staging_areas);

	const std::vector<action_ptr> &get_all_actions() const;

	friend std::ostream& operator<<(std::ostream& os, const City& r);
private:

	void refresh_all_actions();

	std::vector<Request> requests;
	std::vector<Landfill> land_fills;
	std::vector<StagingArea> staging_areas;

	std::vector<action_ptr> all_actions;
};

#endif /* CITY_H_ */
