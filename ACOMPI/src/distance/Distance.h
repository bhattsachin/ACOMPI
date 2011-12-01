/*
 * Distance.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef DISTANCE_H_
#define DISTANCE_H_

#include "../DataStructure.h"
#include<math.h>

class Distance {

public:
	long compute(long x, long y, DataStructure::Point *nodeptr);
public:
	Distance();
	virtual ~Distance();

	static double dtrunc (double x)
	{
	    int k;

	    k = (int) x;
	    x = (double) k;
	    return x;
	}



};

#endif /* DISTANCE_H_ */
