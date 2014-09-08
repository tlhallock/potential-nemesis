/*
 * TextWriter.cpp
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#include "TextWriter.h"

#include "common.h"

#include <algorithm>
#include <map>

#define DELIM "\t"

#if 0

namespace
{
	std::map <Operation, char> o2a;
	std::map <char, Operation> a2o;

	void fill_map()
	{
		if (o2a.size() == 0)
		{
			return;
		}

		o2a.insert(std::pair<Operation, char>{PickUp, 'P'});
		a2o.insert(std::pair<char, Operation>{'P', PickUp});

		o2a.insert(std::pair<Operation, char>{DropOff, 'D'});
		a2o.insert(std::pair<char, Operation>{'D', DropOff});
	}

	char get_a(Operation o)
	{

	}
}

std::vector<Request>* load_requests(std::string filename)
{
	std::ifstream input_file { filename };

	std::vector<Request> *ret_val = new std::vector<Request>;
	return ret_val;
}

void save_requests(std::string filename, const std::vector<Request>& requests)
{
	std::ofstream output_file { filename };
	std::for_each(requests.begin(), requests.end(), [&output_file](const Request &r)
	{
		output_file << r.get_x() << DELIM << r.get_y() << DELIM <<  r.get_operation() << std::endl;
	});
}

#endif
