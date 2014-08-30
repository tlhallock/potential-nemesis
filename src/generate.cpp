
#include "generate.h"

#include "common.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

#include <set>

double generate_coord()
{
	return  DIM_MAX * (rand() / (double) RAND_MAX);
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
	sh_time_t time = rand() % sh_time_look_ahead;
	return Request { generate_location(), genereate_operation(), time - sh_time_window, time + sh_time_window };
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
