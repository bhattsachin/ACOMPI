/*
 * Solution.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef SOLUTION_H_
#define SOLUTION_H_

#include "Library.h"
#include "Ants.h"

class Solution {

public:
	Ants::Ant *best_so_far_ant; /* struct that contains the best-so-far ant */
	Ants::Ant *restart_best_ant; /* struct that contains the restart-best ant */

	long *best_in_try;
	long *best_found_at;
	double *time_best_found;
	double *time_total_run;

public:
	Solution();
	virtual ~Solution();
};

#endif /* SOLUTION_H_ */
