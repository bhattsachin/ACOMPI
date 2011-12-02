/*
 * AcoRun.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "AcoRun.h"

AcoRun::AcoRun() {
	// TODO Auto-generated constructor stub

}

AcoRun::~AcoRun() {
	// TODO Auto-generated destructor stub
}

void AcoRun::init(int argc, char **argv) {
	char* fileName = argv[1];

	reader.readFile(fileName, &cities);
	cout << "number of ants:" << cities.number_of_cities << endl;

	//compute distance
	cities.compute_distances(cities.instance.nodeptr);

}

/**
 * when code is run on slave nodes
 * we must pass this value
 */
void AcoRun::initAllNodes(Cities citiesPtr) {
	cities = citiesPtr;

	//allocate ants
	allocateAnts();

	//think this should be out of all loops
	//compute_near_neighbourhood_list
	cities.compute_near_neighbourhood_list(ants);

}

/**
 * initializes pheromone trails
 */
void AcoRun::generatePheromone() {

	cities.pheromone = cities.util.generate_double_matrix(
			cities.number_of_cities, cities.number_of_cities);
	cities.total = cities.util.generate_double_matrix(cities.number_of_cities,
			cities.number_of_cities);

}

void AcoRun::allocateAnts() {
	long int i;

	if ((ants.ant = (Ants::Ant *) malloc(
			sizeof(Ants::Ant) * ants.number_of_ants + sizeof(Ants::Ant *)
					* ants.number_of_ants)) == NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}
	for (i = 0; i < ants.number_of_ants; i++) {
		ants.ant[i].tour = (long *) calloc(cities.number_of_cities + 1,
				sizeof(long));
		ants.ant->visited = (char *) calloc(cities.number_of_cities,
				sizeof(char));
	}

	if ((solution.best_so_far_ant = (Ants::Ant *) malloc(sizeof(Ants::Ant)))
			== NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}
	(*solution.best_so_far_ant).tour = (long *) calloc(
			cities.number_of_cities + 1, sizeof(long));
	(*solution.best_so_far_ant).visited = (char *) calloc(
			cities.number_of_cities, sizeof(char));

	if ((solution.restart_best_ant = (Ants::Ant *) malloc(sizeof(Ants::Ant)))
			== NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}
	(*solution.restart_best_ant).tour = (long *) calloc(
			cities.number_of_cities + 1, sizeof(long));
	(*solution.restart_best_ant).visited = (char *) calloc(
			cities.number_of_cities, sizeof(char));

	if ((ants.prob_of_selection = (double *) malloc(
			sizeof(double) * ants.nearest_neighbourhood)) == NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}

}

void AcoRun::initializeTry(long ntry) {

	//start_timers();
	//time_used = elapsed_time( VIRTUAL );
	//time_passed = time_used;

	//fprintf(comp_report,"seed %ld\n",seed);

	/* Initialize variables concerning statistics etc. */

	solution.number_of_tours = 1;
	solution.iteration = 1;
	solution.restart_iteration = 1;
	solution.lambda = 0.05;
	solution.best_so_far_ant->tour_length = INFTY;
	solution.found_best = 0;

	ants.trail_max = 1. / ((ants.evaporation_param) * cities.nn_tour(ants));
	ants.trail_min = ants.trail_max / (2. * cities.number_of_cities);
	cities.init_pheromone_trails(ants.trail_max);

	/* Calculate combined information pheromone times heuristic information */
	cities.compute_total_information(ants);

	cout << "trial begins: " << ntry << endl;

}

/**
 * checks whether termination condition is met
 */
bool AcoRun::termination_condition(long max_tours) {
	return (solution.number_of_tours >= max_tours);
}

/**
 * manage the solution construction phase
 */
void AcoRun::construct_solutions(void) {
	long int k; /* counter variable */
	long int step; /* counter of the number of construction steps */

	/* Mark all cities as unvisited */
	for (k = 0; k < ants.number_of_ants; k++) {
		ants.ant_empty_memory(&ants.ant[k], ants.number_of_ants);
	}

	step = 0;
	/* Place the ants on same initial city */
	for (k = 0; k < ants.number_of_ants; k++)
		cities.place_ant(&ants.ant[k], step, cities.number_of_cities);

	while (step < cities.number_of_cities - 1) {
		step++;
		for (k = 0; k < ants.number_of_ants; k++) {
			cities.neighbour_choose_and_move_to_next(&ants.ant[k], step, ants);
		}
	}

	step = cities.number_of_cities;
	for (k = 0; k < ants.number_of_ants; k++) {
		ants.ant[k].tour[cities.number_of_cities] = ants.ant[k].tour[0];
		ants.ant[k].tour_length = cities.compute_tour_length(ants.ant[k].tour);

	}
	solution.number_of_tours += ants.number_of_ants;
}

/**
 * manage some statistical information about the trial, especially
 if a new best solution (best-so-far or restart-best) is found and
 adjust some parameters if a new best solution is found
 */
void AcoRun::update_statistics(void)
/*
 FUNCTION:
 INPUT:          none
 OUTPUT:         none
 (SIDE)EFFECTS:  restart-best and best-so-far ant may be updated; trail_min
 and trail_max used by MMAS may be updated
 */
{

	long iteration_best_ant;
	double p_x; /* only used by MMAS */

	iteration_best_ant = cities.find_best(ants); /* iteration_best_ant is a global variable */

	if (ants.ant[iteration_best_ant].tour_length
			< (*solution.best_so_far_ant).tour_length) {

		//time_used = elapsed_time( VIRTUAL ); /* best sol found after time_used */
		ants.copy_from_to(&ants.ant[iteration_best_ant], ants.best_so_far_ant,
				cities.number_of_cities);
		ants.copy_from_to(&ants.ant[iteration_best_ant], ants.restart_best_ant,
				cities.number_of_cities);

		solution.found_best = solution.iteration;
		solution.restart_found_best = solution.iteration;
		solution.found_branching = node_branching(solution.lambda);
		solution.branching_factor = solution.found_branching;

		p_x = exp(log(0.05) / cities.number_of_cities);
		ants.trail_min = 1. * (1. - p_x) / (p_x
				* (double) ((ants.number_of_ants + 1) / 2));
		ants.trail_max = 1. / ((ants.evaporation_param)
				* (*ants.best_so_far_ant).tour_length);
		//trail_0 = ants.trail_max;
		ants.trail_min = ants.trail_max * ants.trail_min;

		//write_report();
	}
	if (ants.ant[iteration_best_ant].tour_length
			< (*ants.restart_best_ant).tour_length) {
		ants.copy_from_to(&ants.ant[iteration_best_ant],
				solution.restart_best_ant, cities.number_of_cities);
		solution.restart_found_best = solution.iteration;
		//printf("restart best: %ld, restart_found_best %ld, time %.2f\n",(*ants.restart_best_ant).tour_length, solution.restart_found_best, elapsed_time ( VIRTUAL ));
	}
}

double AcoRun::node_branching(double l)
/*
 FUNCTION:       compute the average node lambda-branching factor
 INPUT:          lambda value
 OUTPUT:         average node branching factor
 (SIDE)EFFECTS:  none
 COMMENTS:       see the ACO book for a definition of the average node
 lambda-branching factor
 */
{
	long i, m;
	double min, max, cutoff;
	double avg;
	double *num_branches;

	num_branches = (double *) calloc(cities.number_of_cities, sizeof(double));

	for (m = 0; m < cities.number_of_cities; m++) {
		/* determine max, min to calculate the cutoff value */
		min = cities.pheromone[m][cities.instance.nn_list[m][1]];
		max = cities.pheromone[m][cities.instance.nn_list[m][1]];
		for (i = 1; i < ants.number_of_ants; i++) {
			if (cities.pheromone[m][cities.instance.nn_list[m][i]] > max)
				max = cities.pheromone[m][cities.instance.nn_list[m][i]];
			if (cities.pheromone[m][cities.instance.nn_list[m][i]] < min)
				min = cities.pheromone[m][cities.instance.nn_list[m][i]];
		}
		cutoff = min + l * (max - min);

		for (i = 0; i < ants.number_of_ants; i++) {
			if (cities.pheromone[m][cities.instance.nn_list[m][i]] > cutoff)
				num_branches[m] += 1.;
		}
	}
	avg = 0.;
	for (m = 0; m < cities.number_of_cities; m++) {
		avg += num_branches[m];
	}
	free(num_branches);
	/* Norm branching factor to minimal value 1 */
	return (avg / (double) (cities.number_of_cities * 2));
}

/**
 * manage global pheromone trail update for the ACO algorithms
 */
void AcoRun::pheromone_trail_update(void) {
	cities.evaporation(ants);

	mmas_update();

	/* check pheromone trail limits for MMAS; not necessary if local
	 search is used, because in the local search case lower pheromone trail
	 limits are checked in procedure mmas_evaporation_nn_list */

	cities.check_pheromone_trail_limits(ants);

	/* Compute combined information pheromone times heuristic info after
	 the pheromone update for all ACO algorithms except ACS; in the ACS case
	 this is already done in the pheromone update procedures of ACS */

	cities.compute_total_information(ants);

}

/**
 *  manage global pheromone deposit for MAX-MIN Ant System
 */
void AcoRun::mmas_update( void )
{
    /* we use default upper pheromone trail limit for MMAS and hence we
       do not have to worry regarding keeping the upper limit */

    long iteration_best_ant;
    if ( solution.iteration % ants.u_gb ) {
	iteration_best_ant = cities.find_best(ants);
	cities.global_update_pheromone( &ants.ant[iteration_best_ant] );
    }
    else {
        if ( ants.u_gb == 1 && (solution.iteration - solution.restart_found_best > 50))
	    cities.global_update_pheromone( solution.best_so_far_ant );
        else
	    cities.global_update_pheromone( solution.restart_best_ant );
    }


	ants.u_gb = 25;

}


/**
 * save some statistical information on a trial once it finishes
 */
void AcoRun::exit_try( long ntry )
{
  checkTour( (*solution.best_so_far_ant).tour );
  printf("\n Best Solution in try %ld is %ld\n",ntry, (*solution.best_so_far_ant).tour_length);
  //fprintf(report,"Best: %ld\t Iterations: %6ld\t B-Fac %.5f\t Time %.2f\t Tot.time %.2f\n", (*solution.best_so_far_ant).tour_length, solution.found_best, solution.found_branching, 10000, 10000);
  printf(" Best Solution was found after %ld iterations\n", solution.found_best);

  solution.best_in_try[ntry] = (*solution.best_so_far_ant).tour_length;
  solution.best_found_at[ntry] = solution.found_best;
  solution.time_best_found[ntry] = 10000; //time used
  solution.time_total_run[ntry] = 100000; //time used
  printf("\ntry %ld, Best %ld, found at iteration %ld, found at time %f\n",ntry, solution.best_in_try[ntry], solution.best_found_at[ntry], solution.time_best_found[ntry]);

  //fprintf(comp_report,"end try %ld\n\n",ntry);
  //fprintf(stat_report,"end try %ld\n\n",ntry);
  //TRACE (output_solution();)
  //fflush(report);
  //fflush(comp_report);
  //fflush(stat_report);

}

/**
 * make a simple check whether tour *t can be feasible
 */
void AcoRun::checkTour( long *t )
{
    long i, sum=0;

    for( i = 0 ; i < cities.number_of_cities ; i++ ) {
	sum += t[i];
    }
    if ( sum != (cities.number_of_cities-1) * cities.number_of_cities / 2 ) {
	fprintf(stderr,"Next tour must be flawed !!\n");
	//printTour( t );
	exit(1);
    }
}


