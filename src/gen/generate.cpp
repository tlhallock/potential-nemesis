
#include "generate.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

#include <set>

double generate_coord()
{
	return 100 * (rand() / (double) RAND_MAX);
}

Location generate_location()
{
	return Location{generate_coord(), generate_coord()};
}

Operation genereate_operation()
{
	switch(rand() % 2)
	{
	case 0:
		return DropOff;
	case 1:
		return PickUp;
	default:
		std::cout << "Impossible state" << std::endl;
	}
	return DropOff;
}

Request generate_request()
{
	sh_time_t time = rand() % 1000;
	return Request { generate_location(), genereate_operation(), time - 50, time + 50 };
}

std::vector<Request> generate_requests(int num)
{
	std::vector<Request> requests;
	for (int i = 0; i < num; i++)
	{
		requests.push_back(generate_request());
	}

	return requests;
}

std::vector<Location>* generate_landfills()
{
	std::vector<Location> *ret = new std::vector<Location>;
	for (int i = 0; i < 2; i++)
	{
		ret->push_back(generate_location());
	}
	return ret;
}
