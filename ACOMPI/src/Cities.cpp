/*
 * Cities.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "Cities.h"

Cities::Cities() {
	// TODO Auto-generated constructor stub

}

Cities::~Cities() {
	// TODO Auto-generated destructor stub
}

void Cities::compute_distances(DataStructure::Point *nodeptr)
/*
 FUNCTION: computes the matrix of all intercity distances
 INPUT:    none
 OUTPUT:   pointer to distance matrix, has to be freed when program stops
 */
{
	long i, j;
	cout << "distance is:" << number_of_cities << endl;

	if ((instance.distance = (long **) malloc(
			sizeof(long) * number_of_cities * number_of_cities + sizeof(long *)
					* number_of_cities)) == NULL) {
		fprintf(stderr, "Out of memory, exit.");
		exit(1);
	}
	for (i = 0; i < number_of_cities; i++) {
		instance.distance[i] = (long *) (instance.distance + number_of_cities)
				+ i * number_of_cities;
		for (j = 0; j < number_of_cities; j++) {
			instance.distance[i][j] = distance.compute(i, j, nodeptr);
		}
	}

}

void Cities::compute_near_neighbourhood_list(Ants ants) {
	long int i, node, nn;
	long int *distance_vector;
	long int *help_vector;
	long int **m_nnear;

	TRACE ( printf("\n computing nearest neighbor lists, "); )

	nn = MAX(ants.nearest_neighbour_localsearch,ants.nearest_neighbourhood);
	if (nn >= number_of_cities)
		nn = number_of_cities - 1;
	//DEBUG ( assert( n > nn ); )

	TRACE ( printf("nn = %ld ... \n",nn); )

	if ((m_nnear = (long **) malloc(
			sizeof(long) * number_of_cities * nn + number_of_cities
					* sizeof(long *))) == NULL) {
		exit(EXIT_FAILURE);
	}
	distance_vector = (long *) calloc(number_of_cities, sizeof(long));
	help_vector = (long *) calloc(number_of_cities, sizeof(long));

	for (node = 0; node < number_of_cities; node++) { /* compute cnd-sets for all node */
		m_nnear[node] = (long int *) (m_nnear + number_of_cities) + node * nn;

		for (i = 0; i < number_of_cities; i++) { /* Copy distances from nodes to the others */
			distance_vector[i] = instance.distance[node][i];
			help_vector[i] = i;
		}
		distance_vector[node] = LONG_MAX; /* city is not nearest neighbour */
		util.sort2(distance_vector, help_vector, 0, number_of_cities - 1);
		for (i = 0; i < nn; i++) {
			m_nnear[node][i] = help_vector[i];
		}
	}
	free(distance_vector);
	free(help_vector);
	TRACE ( printf("\n    .. done\n"); )
	instance.nn_list = m_nnear;

}
