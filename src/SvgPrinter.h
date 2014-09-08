/*
 * SvgPrinter.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef SVGPRINTER_H_
#define SVGPRINTER_H_

#include "Solution.h"
#include "model/City.h"


// Might should move these to their classes...
void svg_print_city(const std::string &filename, const City &city);
void svg_print_solution(const std::string &filename, const Solution *solution);

#endif /* SVGPRINTER_H_ */
