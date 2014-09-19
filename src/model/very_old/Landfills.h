/*
 * Landfills.h
 *
 *  Created on: Aug 26, 2014
 *      Author: thallock
 */

#ifndef LANDFILLS_H_
#define LANDFILLS_H_

#include "model/Location.h"
#include "XmlObject.h"

#include <vector>

class Landfill : public Location, XmlObject
{
public:
	Landfill();
	Landfill(const Location &loc, sh_time_t wait_time);
	~Landfill();

	sh_time_t get_wait_time() const;

	friend std::ostream& operator<<(std::ostream& os, const Landfill& r);
	virtual void loadXml(const tinyxml2::XMLElement* element);
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const;
private:
	sh_time_t wait_time;
};

#endif /* LANDFILLS_H_ */
