
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

void test_solver(Solver &&solver, const City *requests, bool best_of_many = true)
{
	std::cout << "city = " << requests << std::endl;

	std::string name = solver.get_name();
	const Parameters &p = solver.get_params();
	Solution sol = solver.solve(*requests);
	std::cout << "Optimal " << name << " solution n=" << sol.get_num_requests_serviced() << std::endl;
	svg_print_solution(name, sol, p);
	std::ofstream log {"sol." + name + ".txt" };
	log << sol << std::endl;


	{
		sol.XmlRootObject::saveXml(stdout);
		sol.XmlRootObject::saveXml("test_sol.xml");
		std::cout << "Saving " << sol << std::endl;

		Solution another {requests};
		another.XmlRootObject::loadXml("test_sol.xml");
		another.XmlRootObject::saveXml(stdout);
	}
}

int main(int argc, char **argv)
{
#if 0
	Current and next things I am working on:
		1. Finish writing the saveXml/loadXml
			rename saveXml -> save_xml
			combine everything under a single interface
		2. Implement the maximum number of containers at each staging area
		4. Finish implementing the genetic algorithm
			right now I am working on the breed function
			Almost all the stubs are empty...
		5. Add helpfull messages when Route.loadXml fails... almost all the logic for a validator should be there.
		6. This could use some unit tests :)
		7. Break off the main methods into: validate <city> <solution>, generate random city <out file>, solve methods <city> <outfile>
			Probably this will mean making a static .a file and compiling several main files against it.
			In the process, I should give this a real Makefile, instead of just using eclipse configs.
		8. Make the parameters also have a saveXml and loadXml method
			The Parameters class is passed around all the time, should this be static?
			Need to add types of distributions to this xml file too
		9. start profiling: I have some guesses why some of this is so slow...
			cache the get_time_taken()
			cache the already_services()
			5% of time is spent in shared_ptr<Action>
			5% of time is spent in get_distance
				I would like to use a distance table instead of calculate distances every the time
				This should be input into the algorithm (instead of x,y points? but then how would we plot it?)
		10. I should clean up the code, and maybe add comments.
			saveXml(bad parameter name)
			Action.get_points() is a bad name
		11. Should the spoke solution also spoke staging?
				maybe I should ensure staging areas are close to landfills
		12. Right now, in optimization utils, I do not consider paths that have have length more than two from a request (store->unstore->request)
		13. Add constraints to each request on which driver they can be attended by.
#endif

	srand(time(NULL));
	//srand(5000013);
	Parameters p;

	City *city = generate_city(p);
	city->XmlRootObject::saveXml("city.xml");
	city->XmlRootObject::saveXml(stdout);

	svg_print_city("random", city, p);

	{
		std::ofstream log { "requests.txt" };
		log << city << std::endl;
		std::cout << city << std::endl;
	}

	int num_to_try = 100;

	test_solver(BestOfManySolver { new RandomGeneratorSolver {p}, num_to_try }, city);

//	test_solver(BestOfManySolver { new NearestPointSolver {p},    num_to_try }, city);
//	test_solver(BestOfManySolver { new SpokeSolver {p},           num_to_try }, city);

	// Right now, these should be about equivalent because the genetic solver doesn't have any breeding/mutation
//	test_solver(GeneticSolver {p, num_to_try, new RandomGeneratorSolver {p}, 50, new SubcycleBreeder{}}, city, false);
//	test_solver(GeneticSolver {p, num_to_try, new NearestPointSolver {p}},    city, false);
//	test_solver(GeneticSolver {p, num_to_try, new SpokeSolver {p}},           city, false);

//	std::cout << "total=" << city.get_num_requests() << std::endl;

	return 0;
}

