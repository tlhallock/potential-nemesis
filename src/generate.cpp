
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
	switch(rand() % 3)
	{
	case 0:
		return DropOff;
	case 1:
		return PickUp;
	case 2:
		return Replace;
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

std::vector<Landfill> generate_landfills(int num)
{
	std::vector<Landfill> ret;
	for (int i = 0; i < num; i++)
	{
		ret.push_back(Landfill{generate_location()});
	}
	return ret;
}

std::vector<StagingArea> generate_staging_areas(int num)
{
	std::vector<StagingArea> ret;
	for (int i = 0; i < num; i++)
	{
		ret.push_back(StagingArea{generate_location(), 0, INT_MAX});
	}
	return ret;
}

City generate_city(const Parameters &p)
{
	City c;

	c.set_requests(generate_requests(p.num_random_requests()));
	c.set_land_fills(generate_landfills(p.num_random_land_fills()));
	c.set_staging_areas(generate_staging_areas(p.num_random_land_fills()));

	return c;
}
