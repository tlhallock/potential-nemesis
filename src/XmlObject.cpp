/*
 * XmlObject.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: thallock
 */

#include "XmlObject.h"

XmlObject::XmlObject() {}
XmlObject::~XmlObject() {}

XmlRootObject::XmlRootObject() {}
XmlRootObject::~XmlRootObject() {}

void XmlRootObject::saveXml(FILE *fp) const
{
	tinyxml2::XMLDocument document;
	saveXml(&document);

	fprintf(fp, "<?xml version=\"1.0\"?>\n");
	document.SaveFile(fp);
}

void XmlRootObject::saveXml(const std::string& filename) const
{
	saveXml(filename.c_str());
}

void XmlRootObject::saveXml(const char* filename) const
{
	FILE *out = fopen(filename, "w");
	saveXml(out);
	fclose(out);
}

void XmlRootObject::loadXml(const std::string& filename)
{
	tinyxml2::XMLDocument document;
	document.LoadFile(filename.c_str());
	loadXml(&document);
}
