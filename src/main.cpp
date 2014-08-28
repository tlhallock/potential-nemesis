
#include "gen/generate.h"

#include "Parameters.h"
#include "gen/RandomNextGenerator.h"

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

	int num_serviced = 0;
	int64_t time = 1000000;

	Route r;

	RandomNextGenerator gen;

	int count = 0;
	for (;;)
	{
		if (count++ > 1000)
		{
			break;
		}

		Solution next = gen.generate(requests, p);

		if (next.get_num_requests_serviced() <= num_serviced)
		{
			continue;
		}

		if (next.get_time_taken() >= time)
		{
			continue;
		}

		count = 0;

		time = next.get_time_taken();
		num_serviced = next.get_num_requests_serviced();

		std::cout << "Found new solution: " << next << std::endl;
	}
}
