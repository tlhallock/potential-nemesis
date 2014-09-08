
#include "generate.h"

#include "common.h"

#include <vector>
#include <cstdlib>
#include <algorithm>

#include <set>

double generate_coord(const Parameters &p)
{
	return  p.get_scale() * (rand() / (double) RAND_MAX);
}

Location generate_location(const Parameters &p)
{
	return Location{generate_coord(p), generate_coord(p)};
}

Operation genereate_operation()
{

	double choice = rand() / (double) RAND_MAX;
	// P(D) = .45
	// P(P) = .45
	// P(R) = .10

	if (choice < .45)
	{
		return DropOff;
	}
	else if (choice < (.45 + .45))
	{
		return PickUp;
	}
	else
	{
		return Replace;
	}
}

Request generate_request(const Parameters &p)
{
	sh_time_t time = rand() % sh_time_look_ahead;
	return Request { generate_location(p), genereate_operation(), time - sh_time_window, time + sh_time_window };
}

std::vector<Request> generate_requests(const Parameters &p)
{
	std::vector<Request> requests;
	for (int i = 0; i < p.num_random_requests(); i++)
	{
		requests.push_back(generate_request(p));
	}

	return requests;
}

std::vector<Landfill> generate_landfills(const Parameters &p)
{
	std::vector<Landfill> ret;
	for (int i = 0; i < p.num_random_land_fills(); i++)
	{
		ret.push_back(Landfill{generate_location(p)});
	}
	return ret;
}

std::vector<StagingArea> generate_staging_areas(const Parameters &p)
{
	std::vector<StagingArea> ret;
	for (int i = 0; i < p.num_random_staging_areas(); i++)
	{
		ret.push_back(StagingArea{generate_location(p), 0, INT_MAX});
	}
	return ret;
}

City generate_city(const Parameters &p)
{
	City c;

	c.set_requests(generate_requests(p));
	c.set_land_fills(generate_landfills(p));
	c.set_staging_areas(generate_staging_areas(p));

	return c;
}
