/*
 * SvgPrinter.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef SVGPRINTER_H_
#define SVGPRINTER_H_

#include "Solution.h"

void svg_print_requests(const std::string &filename, const std::vector<Request> &requests);

void svg_print_solution(const std::string &filename, const Solution *solution);

#endif /* SVGPRINTER_H_ */
