/*
 * Run.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include <iostream>
#include <mpi.h>
#include "AcoRun.h"

using namespace std;
using namespace MPI;

int main(int argc, char **argv) {

	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	AcoRun run;


	/**
	 * playing with datatype
	 */

	/**
	Datatype POINT;
	Status Info;

	POINT=DOUBLE.Create_contiguous(2);
	POINT.Commit();







	if(rank==0){
		Cities::Point pt;
			pt.x = 23;
			pt.y = 26;
			cout<<"sending from node zero:"<<pt.x<<" "<<pt.y<<endl;
			COMM_WORLD.Send(&pt,1,POINT,1,52);

	}else{
		Cities::Point pt2;
			pt2.x = 2;
			pt2.y = 6;
			cout<<"before receiving node one: "<<pt2.x<<" "<<pt2.y<<endl;
			COMM_WORLD.Recv(&pt2,1,POINT,0,52,Info);
			cout<<"after receiving node one: "<<pt2.x<<" "<<pt2.y<<endl;
	}












	*/

	Status Info;
	Datatype TWO_DIM;
	TWO_DIM=LONG.Create_vector(532,1,532);
	TWO_DIM.Commit();




	/**
	 * game over
	 */

	long max_tries = 1000;

	if(rank==0){
		cout << "# aco min max algorithm" << endl;

		run.init(argc, argv);
		cout<<"this is fine:"<<endl;
		run.initAllNodes(run.cities);
		cout<<"ist this fine2"<<endl;

		for ( run.solution.number_of_tries = 0 ; run.solution.number_of_tries < max_tries ; run.solution.number_of_tries++ ) {

			run.initializeTry(run.solution.number_of_tries);

			while ( !run.termination_condition(max_tries) ) {

			    run.construct_solutions();

			    //if ( ls_flag > 0 )
				//local_search();

			    run.update_statistics();

			    run.pheromone_trail_update();

			    //search_control_and_statistics();

			    run.solution.iteration++;
			}
			run.exit_try(run.solution.number_of_tries);
		    }
		   // exit_program();






	}


	//more games

/**

	if(rank==0){

				cout<<"sending 2 dimensional from node zero:"<<run.cities.instance.distance[0][531]<<endl;

				COMM_WORLD.Send(&run.cities.instance.distance,1,TWO_DIM,1,52);

		}else{
			cout<<"is it ok"<<endl;
			long distanc[532][532];
			COMM_WORLD.Recv(&distanc,1,TWO_DIM,0,52,Info);
			cout<<"receiving 2 dimensional at node 1:"<<distanc[0][531]<<endl;

		}

*/

	//game ends





	MPI_Finalize();
	cout<<"program ends:"<<endl;


}
