/*
 * generate.cpp
 *
 *  Created on: Sep 23, 2014
 *      Author: thallock
 */

#include "generate.h"

#include "opt/BestOfManySolver.h"
#include "opt/RandomGeneratorSolver.h"
#include "opt/NearestPointSolver.h"
#include "opt/SpokeSolver.h"

#include "gntc/GeneticSolver.h"
#include "gntc/SubcycleBreeder.h"

#include "SvgPrinter.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <unistd.h>

bool generate()
{
	Parameters p;
	City *city = generate_city(p);
	city->XmlRootObject::saveXml("output/city.xml");

	svg_print_city("output/random", city, p);

	std::ofstream matlab { "output/city.m" };
	city->save_to_matlab(matlab);

	std::ofstream log { "output/requests.txt" };
	log << city << std::endl;

	return true;
}
