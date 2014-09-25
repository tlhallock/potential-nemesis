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
#include "model/Operation.h"

#include <iostream>
#include <map>


class Action;

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
	int get_num_dumpsters() const;

	void set_num_of_size(DumpsterSize size, int32_t number);
	int get_num_of_size(DumpsterSize size) const;

	bool can_apply(const Action* action) const;
	void applied(const Action* action);

	friend std::ostream& operator<<(std::ostream &os, const StagingArea& area);
	void loadXml(const tinyxml2::XMLElement* element);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
	std::ostream& save_to_matlab(std::ostream& out) const;
private:
	location loc;
	int32_t capacity;
	std::map<DumpsterSize, int32_t> inventories;
};

#endif /* STAGINGAREA_H_ */
