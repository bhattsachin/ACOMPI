/*
 * Run.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char **argv) {

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank==0)
		cout << "# aco min max algorithm" << endl;

	MPI_Finalize();



}
