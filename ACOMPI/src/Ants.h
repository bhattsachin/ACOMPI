/*
 * Ants.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef ANTS_H_
#define ANTS_H_

class Ants {

public:
	struct Ant {
		long *tour;
		char *visited;
		long tour_length;
	};

	Ant *ant; /* this (array of) struct will hold the colony */
	int number_of_ants;
	double   *prob_of_selection;
	long nearest_neighbourhood;
	long nearest_neighbour_localsearch;

public:
	Ants();
	virtual ~Ants();
};

#endif /* ANTS_H_ */
