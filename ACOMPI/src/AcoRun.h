/*
 * AcoRun.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef ACORUN_H_
#define ACORUN_H_

#include "Library.h"
#include "FileReader.h"
#include "Cities.h"
#include "Solution.h"


class AcoRun {

public:
	FileReader reader;
	Cities cities;
	Solution solution;
	Ants ants;

public:
	AcoRun();
	virtual ~AcoRun();

	void init(int argc, char **argv);
	void initAllNodes(Cities citiesPtr);
	void allocateAnts(void);
	void generatePheromone();
	void initializeTry(long ntry);
	bool termination_condition(long max_tours);
	void construct_solutions(void);
	void update_statistics(void);
	double node_branching(double l);
	void pheromone_trail_update( void );
	void mmas_update( void );
	void exit_try( long ntry );
	void checkTour( long *t );
};

#endif /* ACORUN_H_ */
