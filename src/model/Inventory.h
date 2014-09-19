/*
 * Inventory.h
 *
 *  Created on: Sep 19, 2014
 *      Author: thallock
 */

#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <map>

class Inventory
{
public:
	Inventory();
	~Inventory();
private:
	location l;
	std::map<DumpsterSize, int> sizes;
};

#endif /* INVENTORY_H_ */
