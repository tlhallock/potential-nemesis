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

class City
{
public:
	City();
	~City();

	const std::vector<const Location> &get_locations() const;

	const std::vector<const StagingArea> &get_staging_areas() const;
	const std::vector<const Request> &get_requests() const;
	const std::vector<const Landfill> &get_land_fills() const;

	const Landfill &get_closest_landfill(const Location &l) const;
private:
	std::vector<Request> requests;

	std::vector<Landfill> land_fills;
	std::vector<StagingArea> staging_areas;
};

#endif /* CITY_H_ */
