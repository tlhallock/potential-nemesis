
#ifndef GENERATE_H_
#define GENERATE_H_

#include "model/City.h"
#include "Parameters.h"

#include <vector>

double generate_coord();

Location generate_location();

Operation genereate_operation();

Request generate_request();

std::vector<Request> generate_requests(int num);

City generate_city(const Parameters &p);

#endif
