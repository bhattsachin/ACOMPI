/*
 * FileReader.cpp
 *
 *  Created on: Nov 30, 2011
 *      Author: bhatt
 */

#include "FileReader.h"

FileReader::FileReader() {
	// TODO Auto-generated constructor stub

}

FileReader::~FileReader() {
	// TODO Auto-generated destructor stub
}

void FileReader::readFile(const char *fileName, Cities *cities) {

	/*
	 FUNCTION: parse and read instance file
	 INPUT:    instance name
	 OUTPUT:   list of coordinates for all nodes
	 COMMENTS: Instance files have to be in TSPLIB format, otherwise procedure fails
	 */
	{
		FILE *tsp_file;
		char buf[100];
		long int i, j;
		struct DataStructure::Point *nodeptr;

		tsp_file = fopen(fileName, "r");
		if (tsp_file == NULL) {
			fprintf(stderr, "No instance file specified, abort\n");
			exit(1);
		}
		//assert(tsp_file != NULL);
		printf("\nreading tsp-file %s ... \n\n", fileName);

		fscanf(tsp_file, "%s", buf);
		while (strcmp("NODE_COORD_SECTION", buf) != 0) {
			if (strcmp("NAME", buf) == 0) {
				fscanf(tsp_file, "%s", buf);
				printf("%s ", buf);
				fscanf(tsp_file, "%s", buf);
				strcpy(cities->instance.name, buf);
				printf("%s \n", cities->instance.name);
				buf[0] = 0;
			} else if (strcmp("NAME:", buf) == 0) {
				cout<<"are we here point 3"<<endl;
				fscanf(tsp_file, "%s", buf);
				strcpy(cities->instance.name, buf);
				printf("%s \n", cities->instance.name);
				buf[0] = 0;
			} else if (strcmp("COMMENT", buf) == 0) {
				cout<<"how about this point 4"<<endl;
				fgets(buf, 100, tsp_file);
				printf("%s", buf);
				buf[0] = 0;
			} else if (strcmp("COMMENT:", buf) == 0) {
				fgets(buf, 100, tsp_file);
				printf("%s", buf);
				buf[0] = 0;
			} else if (strcmp("TYPE", buf) == 0) {
				fscanf(tsp_file, "%s", buf);
				printf("%s ", buf);
				fscanf(tsp_file, "%s", buf);
				printf("%s\n", buf);
				if (strcmp("TSP", buf) != 0) {
					fprintf(stderr,
							"\n Not a TSP instance in TSPLIB format !!\n");
					exit(1);
				}
				buf[0] = 0;
			} else if (strcmp("TYPE:", buf) == 0) {
				fscanf(tsp_file, "%s", buf);
				printf("%s\n", buf);
				if (strcmp("TSP", buf) != 0) {
					fprintf(stderr,
							"\n Not a TSP instance in TSPLIB format !!\n");
					exit(1);
				}
				buf[0] = 0;
			} else if (strcmp("DIMENSION", buf) == 0) {
				fscanf(tsp_file, "%s", buf);
				printf("%s ", buf);
				fscanf(tsp_file, "%ld", &cities->number_of_cities);
				//instance.n = n;
				printf("%ld\n", cities->number_of_cities);
				//assert ( n > 2 && n < 6000);
				buf[0] = 0;
			} else if (strcmp("DIMENSION:", buf) == 0) {
				fscanf(tsp_file, "%ld", &cities->number_of_cities);
				//instance.n = n;
				printf("%ld\n", cities->number_of_cities);
				//assert ( n > 2 && n < 6000);
				buf[0] = 0;
			} else if (strcmp("DISPLAY_DATA_TYPE", buf) == 0) {
				fgets(buf, 100, tsp_file);
				printf("%s", buf);
				buf[0] = 0;
			} else if (strcmp("DISPLAY_DATA_TYPE:", buf) == 0) {
				fgets(buf, 100, tsp_file);
				printf("%s", buf);
				buf[0] = 0;
			} else if (strcmp("EDGE_WEIGHT_TYPE", buf) == 0) {
				buf[0] = 0;
				fscanf(tsp_file, "%s", buf);
				printf("%s ", buf);
				buf[0] = 0;
				fscanf(tsp_file, "%s", buf);
				printf("%s\n", buf);
				cout<<"all right point 2"<<endl;
				if (strcmp("EUC_2D", buf) == 0) {
					cities->distance = Distance();
				} else if (strcmp("CEIL_2D", buf) == 0) {
					cities->distance = CeilDistance();
				} else if (strcmp("GEO", buf) == 0) {
					cities->distance = GeoDistance();
				} else if (strcmp("ATT", buf) == 0) {
					cities->distance = AttDistance();
				} else
					fprintf(stderr, "EDGE_WEIGHT_TYPE %s not implemented\n",
							buf);
				strcpy(cities->instance.edge_weight_type, buf);
				buf[0] = 0;
			} else if (strcmp("EDGE_WEIGHT_TYPE:", buf) == 0) {
				/* set pointer to appropriate distance function; has to be one of
				 EUC_2D, CEIL_2D, GEO, or ATT. Everything else fails */
				buf[0] = 0;
				fscanf(tsp_file, "%s", buf);
				printf("%s\n", buf);
				printf("%s\n", buf);
				printf("%s\n", buf);
				if (strcmp("EUC_2D", buf) == 0) {
					cities->distance = Distance();
				} else if (strcmp("CEIL_2D", buf) == 0) {
					cities->distance = CeilDistance();
				} else if (strcmp("GEO", buf) == 0) {
					cities->distance = GeoDistance();
				} else if (strcmp("ATT", buf) == 0) {
					cities->distance = AttDistance();
				} else {
					fprintf(stderr, "EDGE_WEIGHT_TYPE %s not implemented\n",
							buf);
					exit(1);
				}
				strcpy(cities->instance.edge_weight_type, buf);
				buf[0] = 0;
			}
			buf[0] = 0;
			fscanf(tsp_file, "%s", buf);
		}

		if (strcmp("NODE_COORD_SECTION", buf) == 0) {
			printf("found section contaning the node coordinates\n");
		} else {
			fprintf(stderr,
					"\n\nSome error ocurred finding start of coordinates from tsp file !!\n");
			exit(1);
		}

		if ((nodeptr = (DataStructure::Point *) malloc(
				sizeof(struct DataStructure::Point) * cities->number_of_cities))
				== NULL)
			exit(EXIT_FAILURE);
		else {
			for (i = 0; i < cities->number_of_cities; i++) {
				fscanf(tsp_file, "%ld %lf %lf", &j, &nodeptr[i].x,
						&nodeptr[i].y);
			}
		}

		cities->instance.nodeptr = nodeptr;

	}
}
