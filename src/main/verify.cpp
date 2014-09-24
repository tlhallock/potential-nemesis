/*
 * verify.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: thallock
 */


#include "Solution.h"
#include "Parameters.h"

void verify()
{
	Parameters p;
	City *city = new City;
	city->XmlRootObject::loadXml("output/city.xml");

	Solution* solution = new Solution {city};

	solution->XmlRootObject::loadXml("output/sol.best_of_many[nearest].xml");
	solution->validate();
	solution->XmlRootObject::loadXml("output/sol.best_of_many[random].xml");
	solution->validate();
	solution->XmlRootObject::loadXml("output/sol.best_of_many[spoke].xml");
	solution->validate();
}

