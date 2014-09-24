/*
 * StagingArea.h
 *
 *  Created on: Sep 23, 2014
 *      Author: thallock
 */

#ifndef STAGINGAREA_H_
#define STAGINGAREA_H_

#include "common.h"
#include "XmlObject.h"

#include <iostream>

class StagingArea
{
public:
	StagingArea();
	StagingArea(	location location,
			int32_t capacity,
			int32_t *initial_capacities);
	~StagingArea();

	int get_location() const;
	int get_capacity() const;
	int get_capacity(int ndx) const;

	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;

	std::ostream& save_to_matlab(std::ostream& out) const;
private:
	location loc;
	int32_t capacity;
	int32_t initial_capacities[4];
};

#endif /* STAGINGAREA_H_ */
