/*
 * GeoDistance.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef GEODISTANCE_H_
#define GEODISTANCE_H_

#include "Distance.h"

class GeoDistance : public Distance{
public:
	GeoDistance();
	virtual ~GeoDistance();
	long compute(long x, long y, DataStructure::Point *nodeptr);
};

#endif /* GEODISTANCE_H_ */
