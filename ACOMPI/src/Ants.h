/*
 * Ants.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef ANTS_H_
#define ANTS_H_

#define FALSE 0

class Ants {

public:
	struct Ant {
		long *tour;
		char *visited;
		long tour_length;
	};

	Ant *ant; /* this (array of) struct will hold the colony */
	Ant *best_so_far_ant;
	Ant *restart_best_ant;

	int number_of_ants;
	double   *prob_of_selection;
	long nearest_neighbourhood;
	long nearest_neighbour_localsearch;
	double   trail_max;       /* maximum pheromone trail in MMAS */
	double   trail_min;       /* minimum pheromone trail in MMAS */
	double evaporation_param;           /* parameter for evaporation */

	double alpha;  /* importance of trail */
	double beta;  /* importance of heuristic evaluate */
	double q_0;           /* probability of best choice in tour construction */
	long u_gb;


public:
	Ants();
	virtual ~Ants();
	void ant_empty_memory( Ants::Ant *a, long number_of_ants  );
	void copy_from_to(Ant *a1, Ant *a2, long number_of_cities);
};

#endif /* ANTS_H_ */
