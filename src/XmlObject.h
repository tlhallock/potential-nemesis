/*
 * XmlObject.h
 *
 *  Created on: Sep 11, 2014
 *      Author: thallock
 */

#ifndef XMLOBJECT_H_
#define XMLOBJECT_H_

#include "common.h"

class XmlObject
{
public:
	XmlObject();
	virtual ~XmlObject();

	virtual void loadXml(const tinyxml2::XMLElement* element) = 0;
	// I have to port the current classes to write to an element, instead of an out stream.
	virtual void saveXml(tinyxml2::XMLElement* element) const = 0;
};

#endif /* XMLOBJECT_H_ */
