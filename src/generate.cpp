
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

Operation generate_request_operation()
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
		die();
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

void generate_requests(const Parameters &p, City *city)
{
	for (int i = 0; i < p.num_random_requests(); i++)
	{
		Operation o = generate_request_operation();

		sh_time_t start_time;
		sh_time_t stop_time;

		generate_times(o, start_time, stop_time);

		location l = city->add_location(generate_location(p));

		// only good for now...
		uint32_t inventory[4];
		inventory[0] = inventory[1] = inventory[2] = inventory[3] = 0;

		city->add_request(new Action
		{
			o,
			gen_in_size(o),
			gen_out_size(o),
			start_time,
			stop_time,
			TIME_AT_HOUSE,
			l
		});
	}
}

void generate_landfills(const Parameters &p, City* city)
{
	// only good for now...
	uint32_t inventory[4];
	inventory[0] = inventory[1] = inventory[2] = inventory[3] = 0;
	for (int i = 0; i < p.num_random_land_fills(); i++)
	{
		city->add_land_fill(generate_location(p));
	}
}

void generate_staging_areas(const Parameters &p, City* city)
{
	// only good for now...
	int inventory[4];
	inventory[0] = inventory[1] = inventory[2] = inventory[3] = 5;

	for (int i = 0; i < p.num_random_staging_areas(); i++)
	{
		city->add_staging_area(generate_location(p), &inventory[0], INT_MAX);

	}
}

TruckType generate_truck_type()
{
	switch (rand() % 3)
	{
		case 0:
			return lithe;
		case 1:
			return normal;
		case 2:
			return strong;
	}
	return normal;
}

void generate_trucks(const Parameters &p, City* city)
{
	for (int i = 0; i < p.get_num_drivers(); i++)
	{
		city->add_truck(generate_truck_type());
	}
}

City *generate_city(const Parameters &p)
{
	City *c = new City;

	c->add_location(generate_location(p)); // start location...

	generate_trucks(p, c);
	generate_requests(p, c);
	generate_landfills(p, c);
	generate_staging_areas(p, c);

	return c;
}
