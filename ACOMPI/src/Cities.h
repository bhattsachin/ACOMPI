/*
 * Cities.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef CITIES_H_
#define CITIES_H_

#define HEURISTIC(m,n)     (1.0 / ((double) instance.distance[m][n] + 0.1))

#include "Library.h"
#include "distance/Distance.h"
#include "Ants.h"
#include "Util.h"

class Cities {



public: struct problem{
  char          name[100];      	 /* instance name */
  char          edge_weight_type[100];  /* selfexplanatory */
  long      optimum;                /* optimal tour length if known, otherwise a bound */
  long      n;                      /* number of cities */
  long     n_near;                 /* number of nearest neighbors */
  struct DataStructure::Point  *nodeptr;               /* array of structs containing coordinates of nodes */
  long     **distance;	        /* distance matrix: distance[i][j] gives distance
					   between city i und j */
  long     **nn_list;              /* nearest neighbor list; contains for each node i a
                                           sorted list of n_near nearest neighbors */
};

problem instance;
Util util;

//name of the file
char* name;
int number_of_cities;
Distance distance; //pointer to function returning distance

double   **pheromone; //pheromone deposits on trails
double   **total;


public:
	Cities();
	virtual ~Cities();
	void compute_distances(DataStructure::Point *nodeptr);
	void compute_near_neighbourhood_list(Ants ants);
	long  nn_tour(Ants ants);
	void place_ant( Ants::Ant *a , long step, long number_of_cities);
	void choose_closest_next( Ants::Ant *a, long phase );
	long compute_tour_length( long *t );
	void init_pheromone_trails( double initial_trail);
	void compute_total_information(Ants ants);
	void neighbour_choose_and_move_to_next( Ants::Ant *a , long int phase, Ants ants );
	void choose_best_next( Ants::Ant *a, long phase );
	void neighbour_choose_best_next( Ants::Ant *a, long int phase, Ants ants );
	long find_best(Ants ants);
	void evaporation(Ants ants);
	void global_update_pheromone( Ants::Ant *a );
	void check_pheromone_trail_limits(Ants ants);
};

#endif /* CITIES_H_ */
