/*
 * common.h
 *
 *  Created on: Aug 28, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <inttypes.h>
#include <climits>

#include <algorithm>

typedef int64_t sh_time_t;
#define sh_time_max LONG_MAX
#define sh_time_min 0
#define sh_time_look_ahead 1000
#define sh_time_window (sh_time_look_ahead / 5)

#define DIM_MAX 100

#define foreach(x,y) do { auto mx = (x); std::for_each(mx.begin(), mx.end(), (y)); } while(0)

#endif /* COMMON_H_ */
