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

	cities.compute_near_neighbourhood_list(ants);

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
		ants.ant->visited = (char *)calloc(cities.number_of_cities, sizeof(char));
	}

	if ((solution.best_so_far_ant = (Ants::Ant *)malloc(sizeof(Ants::Ant))) == NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}
	(*solution.best_so_far_ant).tour = (long *)calloc(cities.number_of_cities + 1,
			sizeof(long));
	(*solution.best_so_far_ant).visited = (char *)calloc(cities.number_of_cities,
			sizeof(char));

	if ((solution.restart_best_ant = (Ants::Ant *)malloc(sizeof(Ants::Ant))) == NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}
	(*solution.restart_best_ant).tour = (long *)calloc(cities.number_of_cities + 1,
			sizeof(long));
	(*solution.restart_best_ant).visited = (char *)calloc(cities.number_of_cities,
			sizeof(char));

	if ((ants.prob_of_selection = (double *)malloc(
			sizeof(double) * ants.nearest_neighbourhood)) == NULL) {
		printf("Out of memory, exit.");
		exit(1);
	}

}

