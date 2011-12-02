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


	//related to each trial
	 long number_of_tours;
	 long iteration;
	 long restart_iteration;
	 long restart_found_best;
	 double lambda;
	 long found_best;
	 long number_of_tries;
	 double   found_branching;   /* branching factor when best solution is found */
	 double   branching_factor;  /* average node branching factor when searching */

public:
	Solution();
	virtual ~Solution();
};

#endif /* SOLUTION_H_ */
