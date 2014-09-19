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

	int get_num_stops() const;
	const Action *get_stop(int index) const;

	sh_time_t get_time_from(int i, int j);

	void add_stop(Action *action);

	const std::vector<const Action *> &get_all_stops() const;

	friend std::ostream& operator<<(std::ostream& os, const City& r);

	void loadXml(const tinyxml2::XMLDocument* document);
	tinyxml2::XMLElement* saveXml(tinyxml2::XMLDocument* document) const;

	int add_location(const Location & l);
private:
	std::vector<Action *> all_actions;
};

#endif /* CITY_H_ */
