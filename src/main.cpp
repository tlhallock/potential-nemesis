
#include "gen/generate.h"

#include "opt/RandomGeneratorSolver.h"

#include <iostream>
#include <algorithm>

#include <unistd.h>

int main(int argc, char **argv)
{
	srand(time(NULL));
	Parameters p;

	std::vector<Request> requests = generate_requests(p.get_num_requests());

	std::sort(requests.begin(), requests.end(), [](const Request &r1, const Request &r2)
			{ return r1.get_minimum_time() < r2.get_minimum_time(); });

	std::for_each(requests.begin(), requests.end(), [](Request &r)
	{
		std::cout << r << std::endl;
	});

	RandomGeneratorSolver solver;

	Solution *s = solver.solve(requests, p);

	std::cout << "Optimal solution: " << *s << std::endl;

	delete s;
}
