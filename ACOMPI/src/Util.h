/*
 * Util.h
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#ifndef UTIL_H_
#define UTIL_H_

#include<iostream>


#define INFTY                 LONG_MAX

#define TRUE  1
#define FALSE 0


/* general macros */

#define MAX(x,y)        ((x)>=(y)?(x):(y))
#define MIN(x,y)        ((x)<=(y)?(x):(y))

#define DEBUG( x )

#define TRACE( x )
/* constants for a random number generator, for details see numerical recipes in C */

#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define MASK 123459876

class Util {
public:
	Util();
	virtual ~Util();

	void sort2(long int v[], long int v2[], long int left, long int right);
	void swap2(long int v[], long int v2[], long int i, long int j);
	double ** generate_double_matrix( long int n, long int m);
	double generate_random_value( long *idum );


};

#endif /* UTIL_H_ */
