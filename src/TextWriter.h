/*
 * TextWriter.h
 *
 *  Created on: Aug 29, 2014
 *      Author: rever
 */

#ifndef TEXTWRITER_H_
#define TEXTWRITER_H_

#include "model/Request.h"

#include <vector>


std::vector *load_requests(std::string filename);
void save_requests(std::string filename, const std::vector<Request> &requests);


#endif /* TEXTWRITER_H_ */
