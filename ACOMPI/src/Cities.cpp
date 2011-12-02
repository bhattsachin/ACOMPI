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
/**
 * generate some nearest neighbor tour and compute tour length
 */
long Cities::nn_tour(Ants ants)
{
	long phase, help;

	ants.ant_empty_memory(&ants.ant[0], number_of_cities);

	phase = 0; /* counter of the construction steps */
	place_ant(&ants.ant[0], phase, number_of_cities);

	while (phase < number_of_cities - 1) {
		phase++;
		//printf("ants: %f", ant[0].tour_length);
		//printf("phase: %f", phase);
		choose_closest_next(&ants.ant[0], phase);
	}
	phase = number_of_cities;
	ants.ant[0].tour[number_of_cities] = ants.ant[0].tour[0];
	//if ( ls_flag ) {
	//two_opt_first( ant[0].tour );
	//}


	//TODO: uncomment & fix this
	//n_tours += 1;

	ants.ant[0].tour_length = compute_tour_length(ants.ant[0].tour);

	help = ants.ant[0].tour_length;
	ants.ant_empty_memory(&ants.ant[0], number_of_cities);
	return help;
}

/**
 *  Chooses for an ant the closest city as the next one
 */
void Cities::choose_closest_next(Ants::Ant *a, long phase) {
	long city, current_city, next_city, min_distance;

	next_city = number_of_cities;
	DEBUG( assert ( phase > 0 && phase < n ); );
	current_city = (*a).tour[phase - 1];
	min_distance = INFTY; /* Search shortest edge */
	for (city = 0; city < number_of_cities; city++) {
		if ((*a).visited[city])
			; /* city already visited */
		else {
			if (instance.distance[current_city][city] < min_distance) {
				next_city = city;
				min_distance = instance.distance[current_city][city];
			}
		}
	}
	//DEBUG( assert ( 0 <= next_city && next_city < n); );
	(*a).tour[phase] = next_city;
	(*a).visited[next_city] = TRUE;
}

/**
 * FUNCTION:      place an ant on a randomly chosen initial city
 */
void Cities::place_ant(Ants::Ant *a, long step, long number_of_cities) {
	long rnd;
	//TODO : fix this
	long seed = 123456;

	rnd
			= (long) (util.generate_random_value(&seed)
					* (double) number_of_cities); /* random number between 0 .. n-1 */
	(*a).tour[step] = rnd;
	(*a).visited[rnd] = TRUE;
}

/**
 * compute the tour length of tour t
 */
long Cities::compute_tour_length(long *t) {
	int i;
	long tour_length = 0;

	for (i = 0; i < number_of_cities; i++) {
		tour_length += instance.distance[t[i]][t[i + 1]];
	}
	return tour_length;
}

/**
 * initialize pheromone trails
 */
void Cities::init_pheromone_trails(double initial_trail) {
	long int i, j;
	/* Initialize pheromone trails */
	for (i = 0; i < number_of_cities; i++) {
		for (j = 0; j <= i; j++) {
			pheromone[i][j] = initial_trail;
			pheromone[j][i] = initial_trail;
			total[i][j] = initial_trail;
			total[j][i] = initial_trail;
		}
	}
}

/**
 * calculates heuristic info times pheromone for each arc
 */
void Cities::compute_total_information(Ants ants) {
	long i, j;
	for (i = 0; i < number_of_cities; i++) {
		for (j = 0; j < i; j++) {
			total[i][j] = pow(pheromone[i][j], ants.alpha) * pow(
					HEURISTIC(i,j), ants.beta);
			total[j][i] = total[i][j];
		}
	}
}

/**
 * Choose for an ant probabilistically a next city among all unvisited cities in the current city's candidate list.
 */
void Cities::neighbour_choose_and_move_to_next(Ants::Ant *a, long int phase,
		Ants ants) {
	long int i, help;
	long int current_city;
	double rnd, partial_sum = 0., sum_prob = 0.0;
	/*  double   *prob_of_selection; *//* stores the selection probabilities
	 of the nearest neighbor cities */
	double *prob_ptr;

	long seed = 12345;

	if ((ants.q_0 > 0.0) && (util.generate_random_value(&seed) < ants.q_0)) {
		/* with a probability q_0 make the best possible choice
		 according to pheromone trails and heuristic information */
		/* we first check whether q_0 > 0.0, to avoid the very common case
		 of q_0 = 0.0 to have to compute a random number, which is
		 expensive computationally */
		neighbour_choose_best_next(a, phase, ants);
		return;
	}

	prob_ptr = ants.prob_of_selection;

	current_city = (*a).tour[phase - 1]; /* current_city city of ant k */
	DEBUG( assert ( current_city >= 0 && current_city < n ); )
	for (i = 0; i < ants.number_of_ants; i++) {
		if ((*a).visited[instance.nn_list[current_city][i]])
			prob_ptr[i] = 0.0; /* city already visited */
		else {
			DEBUG( assert ( instance.nn_list[current_city][i] >= 0 && instance.nn_list[current_city][i] < n ); )
			prob_ptr[i]
					= total[current_city][instance.nn_list[current_city][i]];
			sum_prob += prob_ptr[i];
		}
	}

	if (sum_prob <= 0.0) {
		/* All cities from the candidate set are tabu */
		choose_best_next(a, phase);
	} else {
		/* at least one neighbor is eligible, chose one according to the
		 selection probabilities */
		rnd = util.generate_random_value(&seed);
		rnd *= sum_prob;
		i = 0;
		partial_sum = prob_ptr[i];
		while (partial_sum <= rnd) {
			i++;
			partial_sum += prob_ptr[i];
		}
		help = instance.nn_list[current_city][i];
		(*a).tour[phase] = help; /* instance.nn_list[current_city][i]; */
		(*a).visited[help] = TRUE;
	}
}

/**
 * chooses for an ant as the next city the one with
 *  maximal value of heuristic information times pheromone
 */
void Cities::choose_best_next(Ants::Ant *a, long int phase) {
	long city, current_city, next_city;
	double value_best;

	next_city = number_of_cities;

	current_city = (*a).tour[phase - 1];
	value_best = -1.; /* values in total matrix are always >= 0.0 */
	for (city = 0; city < number_of_cities; city++) {
		if ((*a).visited[city])
			; /* city already visited, do nothing */
		else {
			if (total[current_city][city] > value_best) {
				next_city = city;
				value_best = total[current_city][city];
			}
		}
	}
	(*a).tour[phase] = next_city;
	(*a).visited[next_city] = TRUE;
}

/**
 * chooses for an ant as the next city the one with
 *maximal value of heuristic information times pheromone
 */
void Cities::neighbour_choose_best_next(Ants::Ant *a, long int phase, Ants ants) {
	long int i, current_city, next_city, help_city;
	double value_best, help;

	next_city = number_of_cities;
	current_city = (*a).tour[phase - 1];
	value_best = -1.; /* values in total matix are always >= 0.0 */
	for (i = 0; i < ants.number_of_ants; i++) {
		help_city = instance.nn_list[current_city][i];
		if ((*a).visited[help_city])
			; /* city already visited, do nothing */
		else {
			help = total[current_city][help_city];
			if (help > value_best) {
				value_best = help;
				next_city = help_city;
			}
		}
	}
	if (next_city == number_of_cities)
		/* all cities in nearest neighbor list were already visited */
		choose_best_next(a, phase);
	else {
		DEBUG( assert ( 0 <= next_city && next_city < n); )
		DEBUG( assert ( value_best > 0.0 ); )
		DEBUG( assert ( (*a).visited[next_city] == FALSE ); )
		(*a).tour[phase] = next_city;
		(*a).visited[next_city] = TRUE;
	}
}

/**
 * find the best ant of the current iteration
 */
long Cities::find_best(Ants ants) {
	long min;
	long k, k_min;

	min = ants.ant[0].tour_length;
	k_min = 0;
	for (k = 1; k < ants.number_of_ants; k++) {
		if (ants.ant[k].tour_length < min) {
			min = ants.ant[k].tour_length;
			k_min = k;
		}
	}
	return k_min;
}

/**
 *  implements the pheromone trail evaporation
 */
void Cities::evaporation(Ants ants) {
	long i, j;
	for (i = 0; i < number_of_cities; i++) {
		for (j = 0; j <= i; j++) {
			pheromone[i][j] = (1 - ants.evaporation_param) * pheromone[i][j];
			pheromone[j][i] = pheromone[i][j];
		}
	}
}

/**
 * reinforces edges used in ant k's solution
 */

void Cities::global_update_pheromone( Ants::Ant *a )
{
    long int i, j, h;
    double   d_tau;
    d_tau = 1.0 / (double) (*a).tour_length;
    for ( i = 0 ; i < number_of_cities ; i++ ) {
	j = (*a).tour[i];
	h = (*a).tour[i+1];
	pheromone[j][h] += d_tau;
	pheromone[h][j] = pheromone[j][h];
    }
}

/**
 * only for MMAS without local search:
  keeps pheromone trails inside trail limits
 */
void Cities::check_pheromone_trail_limits(Ants ants)

{
    long i, j;
    for ( i = 0 ; i < number_of_cities ; i++ ) {
	for ( j = 0 ; j < i ; j++ ) {
	    if ( pheromone[i][j] < ants.trail_min ) {
		pheromone[i][j] = ants.trail_min;
		pheromone[j][i] = ants.trail_min;
	    } else if ( pheromone[i][j] > ants.trail_max ) {
		pheromone[i][j] = ants.trail_max;
		pheromone[j][i] = ants.trail_max;
	    }
	}
    }
}


