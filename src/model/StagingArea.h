/*
 * StagingArea.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef STAGINGAREA_H_
#define STAGINGAREA_H_

#include "model/Location.h"

class StagingArea : public Location
{
public:
	StagingArea();
	StagingArea(const Location &loc,
			sh_time_t wait_time,
			int max_containers);
	virtual ~StagingArea();

	friend std::ostream& operator<<(std::ostream& os, const StagingArea& r);
	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
private:
	sh_time_t wait_time;
	uint32_t max_containers;
};

#endif /* STAGINGAREA_H_ */
