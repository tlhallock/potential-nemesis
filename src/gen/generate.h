
#ifndef GENERATE_H_
#define GENERATE_H_

#include "Route.h"

#include <vector>

double generate_coord();

Location generate_location();

Operation genereate_operation();

Request generate_request();

std::vector<Request> generate_requests(int num);

std::vector<Location>* generate_landfills();

#endif
