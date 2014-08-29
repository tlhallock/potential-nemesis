
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

void test_solver(Solver *slvr, const std::vector<Request> &requests)
{
	BestOfManySolver solver { slvr->get_params(), slvr, 10 };
	Solution *s = solver.solve(requests);
	std::cout << "Optimal " << slvr->get_name() << " solution n=" << s->get_num_requests_serviced() << std::endl;
	svg_print_solution(slvr->get_name(), s);
	delete s;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	Parameters p;

	std::vector<Request> requests = generate_requests(p.get_num_requests());
	std::sort(requests.begin(), requests.end(), [](const Request &r1, const Request &r2)
			{ return r1.get_minimum_time() < r2.get_minimum_time(); });
	svg_print_requests("random", requests);

	{
		std::ofstream log { "requests.txt" };
		foreach(requests, [&log](Request &r)
		{
			std::cout << r << std::endl;
			log << r << std::endl;
		});
	}

	test_solver(new RandomGeneratorSolver {p}, requests);
	test_solver(new NearestPointSolver {p}, requests);
	test_solver(new SpokeSolver {p}, requests);
	std::cout << "total=" << requests.size() << std::endl;

	return 0;
}
