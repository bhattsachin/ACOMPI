/*
 * Ants.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "Ants.h"

Ants::Ants() {
	//get this from params
	number_of_ants = 50;
	nearest_neighbourhood = 20;
	nearest_neighbour_localsearch = 20;
	alpha = 1.0;
	beta = 2.0;
	q_0 = 0.0;
}

Ants::~Ants() {
	// TODO Auto-generated destructor stub
}

/**
 *  FUNCTION:       empty the ants's memory regarding visited cities
 */
void Ants::ant_empty_memory( Ants::Ant *a, long number_of_ants )
{
    long  i;
    for( i = 0 ; i < number_of_ants ; i++ ) {
	(*a).visited[i]=FALSE;
    }
}

/**
 *  copy solution from ant a1 into ant a2
 */
void Ants::copy_from_to(Ant *a1, Ant *a2, long number_of_cities)
{
 int   i;

    (*a2).tour_length = (*a1).tour_length;
    for ( i = 0 ; i < number_of_cities ; i++ ) {
	(*a2).tour[i] = (*a1).tour[i];
    }
    (*a2).tour[number_of_cities] = (*a2).tour[0];
}
