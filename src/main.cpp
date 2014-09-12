
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

void test_solver(Solver &&solver, const City &requests, bool best_of_many = true)
{
	std::string name = solver.get_name();
	const Parameters &p = solver.get_params();
	Solution sol = solver.solve(requests);
	std::cout << "Optimal " << name << " solution n=" << sol.get_num_requests_serviced() << std::endl;
	svg_print_solution(name, sol, p);
	std::ofstream log {"sol." + name + ".txt" };
	log << sol << std::endl;
}

int main(int argc, char **argv)
{
	// to do: add time to the action when the staging area has a time/cost...
	// make a separate action for the an action satisfying a request (request =/= action)

	srand(time(NULL));
	//srand(5000013);
	Parameters p;

	City city = generate_city(p);
	city.saveXml("city.xml");

	svg_print_city("random", city, p);

	{
		std::ofstream log { "requests.txt" };
		log << city << std::endl;
		std::cout << city << std::endl;
	}

	int num_to_try = 100;

	test_solver(BestOfManySolver { new RandomGeneratorSolver {p}, num_to_try }, city);
	test_solver(BestOfManySolver { new NearestPointSolver {p},    num_to_try }, city);
	test_solver(BestOfManySolver { new SpokeSolver {p},           num_to_try }, city);

	// Right now, these should be about equivalent.
	test_solver(GeneticSolver {p, num_to_try, new RandomGeneratorSolver {p}, 50, new SubcycleBreeder{}}, city, false);
	test_solver(GeneticSolver {p, num_to_try, new NearestPointSolver {p}},    city, false);
	test_solver(GeneticSolver {p, num_to_try, new SpokeSolver {p}},           city, false);

	std::cout << "total=" << city.get_num_requests() << std::endl;

	return 0;
}

