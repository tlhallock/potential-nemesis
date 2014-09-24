/*
 * simulate.cpp
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
#include <stdio.h>


void test_solver(Solver &&solver, const City *requests, bool best_of_many = true)
{
	std::string name = solver.get_name();
	const Parameters &p = solver.get_params();
	Solution sol = solver.solve(*requests);
	std::cout << "Optimal " << name << " solution n=" << sol.get_num_requests_serviced() << std::endl;

	svg_print_solution("output/" + name, sol, p);

	sol.XmlRootObject::saveXml("output/sol." + name + ".xml");
	std::ofstream log {"output/sol." + name + ".txt" };
	log << sol << std::endl;
}



void simulate()
{
	int num_to_try = 100;

	Parameters p;
	City *city = new City;
	city->XmlRootObject::loadXml("output/city.xml");


	city->XmlRootObject::saveXml("output/mytest.xml");

	test_solver(BestOfManySolver { new RandomGeneratorSolver {p}, num_to_try }, city);

	test_solver(BestOfManySolver { new NearestPointSolver {p},    num_to_try }, city);
	test_solver(BestOfManySolver { new SpokeSolver {p},           num_to_try }, city);

	// Right now, these should be about equivalent because the genetic solver doesn't have any breeding/mutation
//	test_solver(GeneticSolver {p, num_to_try, new RandomGeneratorSolver {p}, 50, new SubcycleBreeder{}}, city, false);
//	test_solver(GeneticSolver {p, num_to_try, new NearestPointSolver {p}},    city, false);
//	test_solver(GeneticSolver {p, num_to_try, new SpokeSolver {p}},           city, false);

//	std::cout << "total=" << city.get_num_requests() << std::endl;

}
