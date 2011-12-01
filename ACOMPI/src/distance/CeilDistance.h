/*
 * CeilDistance.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef CEILDISTANCE_H_
#define CEILDISTANCE_H_

#include "Distance.h"

class CeilDistance : public Distance{
public:
	CeilDistance();
	virtual ~CeilDistance();
	long compute(long x, long y, DataStructure::Point *nodeptr);
};

#endif /* CEILDISTANCE_H_ */
