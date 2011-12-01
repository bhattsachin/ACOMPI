/*
 * Util.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "Util.h"

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

void Util::sort2(long int v[], long int v2[], long int left, long int right)
/*
      FUNCTION:       recursive routine (quicksort) for sorting one array; second
                      arrays does the same sequence of swaps
      INPUT:          two arrays, two indices
      OUTPUT:         none
      (SIDE)EFFECTS:  elements at position i and j of the two arrays are swapped
*/
{
  long int k, last;

  if (left >= right)
    return;
  swap2(v, v2, left, (left + right)/2);
  last = left;
  for (k=left+1; k <= right; k++)
    if (v[k] < v[left])
      swap2(v, v2, ++last, k);
  swap2(v, v2, left, last);
  sort2(v, v2, left, last);
  sort2(v, v2, last+1, right);
}

void Util::swap2(long int v[], long int v2[], long int i, long int j)
/*
      FUNCTION:       auxiliary routine for sorting an integer array
      INPUT:          two arraya, two indices
      OUTPUT:         none
      (SIDE)EFFECTS:  elements at position i and j of the two arrays are swapped
*/
{
  long int tmp;

  tmp = v[i];
  v[i] = v[j];
  v[j] = tmp;
  tmp = v2[i];
  v2[i] = v2[j];
  v2[j] = tmp;
}
