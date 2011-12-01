/*
 * Cities.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef CITIES_H_
#define CITIES_H_

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


public:
	Cities();
	virtual ~Cities();
	void compute_distances(DataStructure::Point *nodeptr);
	void compute_near_neighbourhood_list(Ants ants);
};

#endif /* CITIES_H_ */
