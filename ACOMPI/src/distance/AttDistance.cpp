/*
 * AttDistance.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "AttDistance.h"
#include<math.h>

AttDistance::AttDistance() {
	// TODO Auto-generated constructor stub

}

AttDistance::~AttDistance() {
	// TODO Auto-generated destructor stub
}

long AttDistance::compute(long i, long j,DataStructure::Point *nodeptr){
	double xd = nodeptr[i].x - nodeptr[j].x;
	    double yd = nodeptr[i].y - nodeptr[j].y;
	    double rij = sqrt ((xd * xd + yd * yd) / 10.0);
	    double tij = dtrunc (rij);
	    long dij;

	    if (tij < rij)
	        dij = (int) tij + 1;
	    else
	        dij = (int) tij;
	    return dij;
}
