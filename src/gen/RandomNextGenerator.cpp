/*
 * RandomNextGenerator.cpp
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#include <gen/RandomNextGenerator.h>

RandomNextGenerator::RandomNextGenerator() {}
RandomNextGenerator::~RandomNextGenerator() {}

Solution RandomNextGenerator::generate(const std::vector<Request>& original_requests, const Parameters &params)
{
	int size = original_requests.size();

	bool *serviced = (bool *) malloc(size);
	for (int i = 0; i < size; i++)
	{
		serviced[i] = 0;
	}

	int num_drivers = params.get_num_drivers();
	Solution s { num_drivers };
	// This is to ensure that solutions don't use the same requests twice...
	for (int i = 0; i < num_drivers; i++)
	{
		generate(original_requests, s.get_route(i), serviced);
	}

	free(serviced);

	return s;
}

void RandomNextGenerator::generate(const std::vector<Request>& original_requests, Route &output, bool *already_serviced)
{
	while (true)
	{
		std::vector<int> possibles;
		for (unsigned int i = 0; i < original_requests.size(); i++)
		{
			const Action& a = original_requests.at(i);
			if (output.can_service_next(a) && !already_serviced[i])
			{
				possibles.push_back(i);
			}
		}

		if (possibles.size() != 0)
		{
			int i = possibles.at(rand() % possibles.size());
			already_serviced[i] = true;
			output.service_next(new Request{original_requests.at(i)});
			continue;
		}

		std::vector<Action> more = output.get_next_possibles();
		if (more.size() != 0)
		{
			output.service_next(new Action{more.at(rand() % more.size())});
			continue;
		}

		return;
	}
}
