/*
 * AttDistance.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef ATTDISTANCE_H_
#define ATTDISTANCE_H_

#include "Distance.h"

class AttDistance : public Distance{
public:
	AttDistance();
	virtual ~AttDistance();
	long compute(long x, long y, DataStructure::Point *nodeptr);
};

#endif /* ATTDISTANCE_H_ */
