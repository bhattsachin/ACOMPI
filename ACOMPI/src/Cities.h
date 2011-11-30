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

class Cities {

public: struct Point {
	  double x;
	  double y;
	};

public: struct problem{
  char          name[100];      	 /* instance name */
  char          edge_weight_type[100];  /* selfexplanatory */
  long int      optimum;                /* optimal tour length if known, otherwise a bound */
  long int      n;                      /* number of cities */
  long int      n_near;                 /* number of nearest neighbors */
  struct point  *nodeptr;               /* array of structs containing coordinates of nodes */
  long int      **distance;	        /* distance matrix: distance[i][j] gives distance
					   between city i und j */
  long int      **nn_list;              /* nearest neighbor list; contains for each node i a
                                           sorted list of n_near nearest neighbors */
};

problem instance;


//name of the file
char* name;
int number_of_cities;
Distance distance; //pointer to function returning distance


public:
	Cities();
	virtual ~Cities();
};

#endif /* CITIES_H_ */
