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
};

#endif /* ACORUN_H_ */
