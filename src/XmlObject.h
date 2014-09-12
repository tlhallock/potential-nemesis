/*
 * XmlObject.h
 *
 *  Created on: Sep 11, 2014
 *      Author: thallock
 */

#ifndef XMLOBJECT_H_
#define XMLOBJECT_H_

#include <tinyxml2.h>
#include <string>

class XmlObject
{
public:
	XmlObject();
	virtual ~XmlObject();

	virtual void loadXml(const tinyxml2::XMLElement* element) = 0;
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLElement* parent) const = 0;
};


class XmlRootObject
{
public:
	XmlRootObject();
	virtual ~XmlRootObject();

	virtual void loadXml(const tinyxml2::XMLDocument* document) = 0;
	virtual tinyxml2::XMLElement* saveXml(tinyxml2::XMLDocument* document) const = 0;

	void saveXml(const char *filename) const;
	void saveXml(const std::string& filename) const;
	void saveXml(FILE *fp) const;

	void loadXml(const std::string& filename);
};

#endif /* XMLOBJECT_H_ */
