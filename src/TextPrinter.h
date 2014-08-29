/*
 * TextPrinter.h
 *
 *  Created on: Aug 29, 2014
 *      Author: thallock
 */

#ifndef TEXTPRINTER_H_
#define TEXTPRINTER_H_

#include "model/Request.h"

#include <vector>

std::vector<Request> *load_requests(const std::string &filename);

void save_requests(const std::string &filename, std::vector<Request> *requests);


#endif /* TEXTPRINTER_H_ */
