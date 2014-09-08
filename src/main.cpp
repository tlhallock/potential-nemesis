
#include "generate.h"

#include "opt/BestOfManySolver.h"
#include "opt/RandomGeneratorSolver.h"
#include "opt/NearestPointSolver.h"
#include "opt/SpokeSolver.h"

#include "SvgPrinter.h"

#include <iostream>
#include <fstream>
#include <algorithm>

#include <unistd.h>

void test_solver(Solver *slvr, const City &requests)
{
	BestOfManySolver solver { slvr->get_params(), slvr, 100 };
	std::unique_ptr<Solution> s {solver.solve(requests)};
	std::cout << "Optimal " << slvr->get_name() << " solution n=" << s->get_num_requests_serviced() << std::endl;
	svg_print_solution(slvr->get_name(), s.get(), slvr->get_params());
	std::ofstream log {"sol." + slvr->get_name() + ".txt" };
	log << *s << std::endl;
}

int main(int argc, char **argv)
{
	// to do: add time to the action when the staging area has a time/cost...
	// make a separate action for the an action satisfying a request (request =/= action)

	srand(time(NULL));
	Parameters p;

	City city = generate_city(p);

	svg_print_city("random", city, p);

	{
		std::ofstream log { "requests.txt" };
		log << city << std::endl;
		std::cout << city << std::endl;
	}

	test_solver(new RandomGeneratorSolver {p}, city);
	test_solver(new NearestPointSolver {p}, city);
	test_solver(new SpokeSolver {p}, city);

	std::cout << "total=" << city.get_num_requests() << std::endl;

	return 0;
}
