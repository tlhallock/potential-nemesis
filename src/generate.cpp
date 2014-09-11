
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

Operation generate_operation()
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

DumpsterSize generate_size()
{
	switch(rand() % 4)
	{
		case 0:
			return smallest;
		case 1:
			return small;
		case 2:
			return big;
		case 3:
			return biggest;
		default:
			return smallest;
	}
}

DumpsterSize gen_in_size(Operation o)
{
	switch (o)
	{
		case DropOff:
		case Replace:
			return generate_size();
		default:
			return none;
	}
}
DumpsterSize gen_out_size(Operation o)
{
	switch (o)
	{
		case PickUp:
		case Replace:
			return generate_size();
		default:
			return none;
	}
}

void generate_times(Operation o, sh_time_t &start_time, sh_time_t &stop_time)
{
	if (rand() % 10 == 0)
	{
		sh_time_t time = rand() % sh_time_look_ahead;
		start_time  = time - sh_time_window;
		stop_time = time + sh_time_window;

		return;
	}
	if (o == PickUp)
	{
		start_time = 0;
		stop_time = sh_time_look_ahead;
		return;
	}

	if (o != Replace && o != DropOff)
	{
		std::cout << "We don't get here, do we?  21351351513327357" << std::endl;
		exit(-1);
	}

	if (rand() % 2 == 0)
	{
		start_time = 0;
		stop_time = sh_time_look_ahead / 2;
		return;
	}

	start_time = sh_time_look_ahead / 2;
	stop_time = sh_time_look_ahead;
}

Request generate_request(const Parameters &p)
{
	Operation o = generate_operation();

	sh_time_t start_time;
	sh_time_t stop_time;

	generate_times(o, start_time, stop_time);

	return Request { generate_location(p),
		o,
		start_time,
		stop_time,
		gen_in_size(o),
		gen_out_size(o)};
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
		ret.push_back(Landfill{generate_location(p), LANDFILL_TIME});
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
