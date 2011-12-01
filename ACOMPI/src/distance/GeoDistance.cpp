/*
 * GeoDistance.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "GeoDistance.h"

GeoDistance::GeoDistance() {
	// TODO Auto-generated constructor stub

}

GeoDistance::~GeoDistance() {
	// TODO Auto-generated destructor stub
}

long GeoDistance::compute(long i, long j, DataStructure::Point *nodeptr) {
	double deg, min;
	double lati, latj, longi, longj;
	double q1, q2, q3;
	long int dd;
	double x1 = nodeptr[i].x, x2 = nodeptr[j].x, y1 = nodeptr[i].y, y2 =
			nodeptr[j].y;

	deg = dtrunc(x1);
	min = x1 - deg;
	lati = M_PI * (deg + 5.0 * min / 3.0) / 180.0;
	deg = dtrunc(x2);
	min = x2 - deg;
	latj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

	deg = dtrunc(y1);
	min = y1 - deg;
	longi = M_PI * (deg + 5.0 * min / 3.0) / 180.0;
	deg = dtrunc(y2);
	min = y2 - deg;
	longj = M_PI * (deg + 5.0 * min / 3.0) / 180.0;

	q1 = cos(longi - longj);
	q2 = cos(lati - latj);
	q3 = cos(lati + latj);
	dd = (int) (6378.388 * acos(0.5 * ((1.0 + q1) * q2 - (1.0 - q1) * q3))
			+ 1.0);
	return dd;

}
