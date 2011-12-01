/*
 * Distance.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "Distance.h"

Distance::Distance() {
	// TODO Auto-generated constructor stub

}

Distance::~Distance() {
	// TODO Auto-generated destructor stub
}

long Distance::compute(long i, long j, DataStructure::Point *nodeptr) {
	double xd = nodeptr[i].x - nodeptr[j].x;
	double yd = nodeptr[i].y - nodeptr[j].y;
	double r = sqrt(xd * xd + yd * yd) + 0.5;

	return (long int) r;
}

