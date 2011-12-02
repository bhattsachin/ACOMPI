/*
 * CeilDistance.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "CeilDistance.h"

CeilDistance::CeilDistance() {
	// TODO Auto-generated constructor stub

}

CeilDistance::~CeilDistance() {
	// TODO Auto-generated destructor stub
}

long CeilDistance::compute(long i, long j, DataStructure::Point *nodeptr){
	double xd = nodeptr[i].x - nodeptr[j].x;
	    double yd = nodeptr[i].y - nodeptr[j].y;
	    double r  = sqrt(xd*xd + yd*yd) + 0.000000001;

	    return (long int)r;
}
